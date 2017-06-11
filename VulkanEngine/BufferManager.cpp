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
	if (Device == VK_NULL_HANDLE)
	{
		return;
	}

	if (UpdateCommandBuffer != VK_NULL_HANDLE)
	{
		vkFreeCommandBuffers(Device, CommandPool, 1, &UpdateCommandBuffer);
		UpdateCommandBuffer = VK_NULL_HANDLE;
	}
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

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = CommandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(Device, &allocInfo, &UpdateCommandBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate scene command buffer!");
	}
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
	if (BeginUpdatesCalled)
	{
		vkEndCommandBuffer(UpdateCommandBuffer);
		BeginUpdatesCalled = false;
	}
	
	//TODO: This is here because a command buffer may be in the middle of using the old buffer when memory is reallocated. Look into better ways to solve this.
	vkDeviceWaitIdle(Device);

	StagingBuffer.Create(
		PhysicalDevice, Device, CommandPool, GraphicsQueue, TotalBufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);
	LocalBuffer.Create(
		PhysicalDevice, Device, CommandPool, GraphicsQueue, TotalBufferSize, 
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
	);

	for (auto buffer : Staged)
	{
		StagingBuffer.Update(buffer);
	}

	Update(Reservations.data(), Reservations.size());
}

void BufferManager::Update(Buffer buffer)
{
	if (BeginUpdatesCalled && buffer.GetSize() <= UINT16_MAX)
	{
		vkCmdUpdateBuffer(UpdateCommandBuffer, buffer.GetHandle(), buffer.GetOffset(), buffer.GetSize(), buffer.GetData());
	}
	else
	{
		StagingBuffer.Update(buffer);
		Staged.push_back(buffer);
	}
}

void BufferManager::Update(Buffer* buffers, size_t bufferCount)
{
	for (size_t i = 0; i < bufferCount; i++)
	{
		Update(buffers[i]);
	}
}

void BufferManager::BeginUpdates()
{
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(UpdateCommandBuffer, &beginInfo);

	BeginUpdatesCalled = true;
}

void BufferManager::EndUpdates()
{
	CopyFromStagingToLocal(Staged.data(), Staged.size());
	Staged.clear();

	if (BeginUpdatesCalled == false)
	{
		return;
	}

	vkEndCommandBuffer(UpdateCommandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &UpdateCommandBuffer;

	vkQueueSubmit(GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	//vkQueueWaitIdle(GraphicsQueue);

	BeginUpdatesCalled = false;
}

void BufferManager::CopyFromStagingToLocal(Buffer* buffers, size_t bufferCount)
{
	if (bufferCount > 1000)
	{
		StagingBuffer.CopyTo(LocalBuffer);
	}
	else
	{
		StagingBuffer.CopyTo(LocalBuffer, buffers, bufferCount);
	}
}
