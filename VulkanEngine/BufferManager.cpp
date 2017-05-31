#include "BufferManager.h"
#include "VulkanHelper.h"

BufferManager::BufferManager()
{
}

BufferManager::BufferManager(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	Initialize(physicalDevice, device, commandPool, graphicsQueue);
}

BufferManager::~BufferManager()
{
}

void BufferManager::Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue)
{
	PhysicalDevice = physicalDevice;
	Device = device;
	CommandPool = commandPool;
	GraphicsQueue = graphicsQueue;

	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(PhysicalDevice, &deviceProperties);
	OffsetAlignment = deviceProperties.limits.minUniformBufferOffsetAlignment;
}

Buffer BufferManager::Reserve(void* data, VkDeviceSize size)
{
	VkDeviceSize alignmentMismatch = size % OffsetAlignment;
	if (alignmentMismatch > 0)
	{
		size += OffsetAlignment - alignmentMismatch;
	}

	if (Vacancies.size() > 0)
	{
		for (size_t i = 0; i < Vacancies.size(); i++)
		{
			Buffer vacancy = Vacancies[i];
			if (vacancy.GetSize() >= size)
			{
				//TODO: Test this.
				if (vacancy.GetSize() > size)
				{
					Vacancies[i] = Buffer(nullptr, LocalBuffer.GetHandlePointer(), vacancy.GetOffset() + size, vacancy.GetSize() - size);
				}
				else
				{
					Vacancies.erase(Vacancies.begin() + i);
				}

				Buffer reservation(data, LocalBuffer.GetHandlePointer(), vacancy.GetOffset(), size);
				Reservations.push_back(reservation);
				return reservation;
			}
		}
	}

	Buffer reservation(data, LocalBuffer.GetHandlePointer(), TotalBufferSize, size);
	Reservations.push_back(reservation);
	TotalBufferSize += size;
	return reservation;
}

void BufferManager::Release(Buffer buffer)
{
	if (buffer == Reservations.back())
	{
		Reservations.pop_back();
		TotalBufferSize -= buffer.GetSize();
	}
	else
	{
		auto position = std::find(Reservations.begin(), Reservations.end(), buffer);
		Reservations.erase(position);
		Vacancies.push_back(buffer);
	}
}

void BufferManager::AllocateReserved()
{
	StagingBuffer.Create(PhysicalDevice, Device, TotalBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	LocalBuffer.Create(PhysicalDevice, Device, TotalBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	Update(Reservations.data(), Reservations.size());
}

void BufferManager::Update(Buffer* buffers, size_t bufferCount)
{
	for (size_t i = 0; i < bufferCount; i++)
	{
		StagingBuffer.Update(buffers[i]);
	}
	
	StagingBuffer.CopyTo(LocalBuffer, buffers, bufferCount, CommandPool, GraphicsQueue);
	//TODO: Find out if it's actually faster to copy the entire buffer at once or only the necessary regions.
}

void BufferManager::Stage(Buffer buffer)
{
	StagingBuffer.Update(buffer);
	Staged.push_back(buffer);
}

void BufferManager::UpdateStaged()
{
	StagingBuffer.CopyTo(LocalBuffer, Staged.data(), Staged.size(), CommandPool, GraphicsQueue);
	Staged.clear();
}
