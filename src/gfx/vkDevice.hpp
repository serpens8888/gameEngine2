#ifndef __VKDEVICE_HPP
#define __VKDEVICE_HPP
#include "../headers.hpp"
#include "vkInstance.hpp"


namespace gfx{


	struct vkDevice {

	static vkDevice * get(vkInstance& instance);

	vkDevice(vkInstance& instance);
	~vkDevice();

	bool suitable(VkPhysicalDevice device);

	u32 deviceCount;
	std::vector<VkPhysicalDevice> devices;
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;




	};











} //namespace gfx

#endif
