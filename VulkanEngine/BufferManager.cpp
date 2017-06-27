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

	FencedCommandBufferPool.Initialize(Device, CommandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 2);
	DeviceBuffer.Initialize(
		PhysicalDevice, Device, CommandPool, GraphicsQueue,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT |
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
	);

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
					Vacancies[i] = Buffer(nullptr, DeviceBuffer.GetHandlePointer(), vacancy.GetOffset() + size, vacancy.GetSize() - size);
				}
				else
				{
					Vacancies.erase(Vacancies.begin() + i);
				}

				Buffer reservation(data, DeviceBuffer.GetHandlePointer(), vacancy.GetOffset(), size);
				Reservations.push_back(reservation);
				return reservation;
			}
		}
	}

	Buffer reservation(data, DeviceBuffer.GetHandlePointer(), TotalBufferSize, size);
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

void BufferManager::Allocate()
{
	EndUpdates();
	SubmitUpdates();

	DeviceBuffer.Resize(TotalBufferSize);

	BeginUpdates();
}

void BufferManager::Update(Buffer buffer)
{
	if (buffer.GetData() == nullptr)
	{
		return;
	}

	if (buffer.GetSize() <= UINT16_MAX)
	{
		vkCmdUpdateBuffer(RecordingCommandBuffer, buffer.GetHandle(), buffer.GetOffset(), buffer.GetSize(), buffer.GetData());
	}
	else
	{
		size_t updateCount = static_cast<size_t>(1 + buffer.GetSize() / UINT16_MAX);
		for (size_t i = 0; i < updateCount; i++)
		{
			VkDeviceSize offset = i * UINT16_MAX;
			VkDeviceSize bufferOffset = buffer.GetOffset() + offset;
			void* dataOffset = static_cast<char*>(buffer.GetData()) + offset;
			VkDeviceSize size = buffer.GetSize() % UINT16_MAX;
			if (size == 0)
			{
				size = UINT16_MAX;
			}
			vkCmdUpdateBuffer(RecordingCommandBuffer, buffer.GetHandle(), bufferOffset, size, dataOffset);
		}
	}
}

void BufferManager::Update(Buffer* buffers, size_t bufferCount)
{
	for (size_t i = 0; i < bufferCount; i++)
	{
		Update(buffers[i]);
	}
}

void BufferManager::UpdateReserved()
{
	Update(Reservations.data(), Reservations.size());
}

void BufferManager::BeginUpdates()
{
	if (RecordingCommandBuffer != VK_NULL_HANDLE)
	{
		return;
	}

	FencedCommandBufferPool.WaitAndGet(&RecordingCommandBuffer, &RecordingFence);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(RecordingCommandBuffer, &beginInfo);
}

void BufferManager::EndUpdates()
{
	if (RecordingCommandBuffer == VK_NULL_HANDLE)
	{
		return;
	}

	vkEndCommandBuffer(RecordingCommandBuffer);

	ExecutableFence = RecordingFence;
	ExecutableCommandBuffer = RecordingCommandBuffer;
	RecordingFence = VK_NULL_HANDLE;
	RecordingCommandBuffer = VK_NULL_HANDLE;
}

void BufferManager::SubmitUpdates()
{
	if (ExecutableCommandBuffer == VK_NULL_HANDLE)
	{
		return;
	}

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &ExecutableCommandBuffer;

	vkResetFences(Device, 1, &ExecutableFence);
	if (vkQueueSubmit(GraphicsQueue, 1, &submitInfo, ExecutableFence) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to submit buffer update!");
	}

	ExecutableCommandBuffer = VK_NULL_HANDLE;
	ExecutableFence = VK_NULL_HANDLE;
}
