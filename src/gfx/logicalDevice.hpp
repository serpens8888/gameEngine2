#ifndef __LOGICALDEVICE_HPP
#define __LOGICALDEVICE_HPP

#include "../headers.hpp"
#include "vkInstance.hpp"
#include "physicalDevice.hpp"
#include "queue.hpp"

namespace gfx{

	struct logicalDevice{

	static logicalDevice * get(physicalDevice& GPU, vkInstance& instance);

	logicalDevice(physicalDevice& GPU, vkInstance& instance);
	~logicalDevice();

	VkDevice device;
	queueFamilyIndices indices;
	VkDeviceQueueCreateInfo queueCreateInfo{};
	float queuePriority;
	VkPhysicalDeviceFeatures deviceFeatures{};
	VkDeviceCreateInfo createInfo{};
	VkQueue graphicsQueue;

	};


} //namespace gfx


#endif
