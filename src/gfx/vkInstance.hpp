#ifndef __VKINTSTANCE_HPP
#define __VKINTSTANCE_HPP

#include "../headers.hpp"

namespace gfx{

struct vkInstance{
	
	static vkInstance * get();

	vkInstance();
	void printExtensions();

	~vkInstance();

	VkInstance instance;
	VkApplicationInfo appInfo;
	VkInstanceCreateInfo createInfo{};

	u32 glfwExtensionCount;
	const char** glfwExtensions;
	u32 layerCount;
	
	std::vector<const char*> validationLayers;
	std::vector<VkLayerProperties> availableLayers;
	std::vector<const char*> extensions;

        bool layerCheck(const std::vector<const char*>& layers, const std::vector<VkLayerProperties>& available);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
							    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* userData);
	VkDebugUtilsMessengerEXT debugMessenger;
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
				              const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
};





}//namespace gfx




#endif
