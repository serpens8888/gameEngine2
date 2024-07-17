#ifndef __PHYSICALDEVICE_HPP
#define __PHYSICALDEVICE_HPP
#include "../headers.hpp"
#include "vkInstance.hpp"
#include "queue.hpp"


namespace gfx{


	struct physicalDevice {

	static physicalDevice * get(vkInstance& instance);

	physicalDevice(vkInstance& instance);
	~physicalDevice();

	bool suitable(VkPhysicalDevice device);

	void printSpecs(VkPhysicalDevice device);

	u32 deviceCount;
	std::vector<VkPhysicalDevice> devices;
	VkPhysicalDevice GPU;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;




	};











} //namespace gfx

#endif
