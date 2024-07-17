#include "vkDevice.hpp"


namespace gfx{


	vkDevice * vkDevice::get(vkInstance& instance){
            static vkDevice * device = new vkDevice(instance);
            return device;
	}

	vkDevice::vkDevice(vkInstance& instance) : deviceCount(0), physicalDevice(VK_NULL_HANDLE){
            deviceCount = 0;
            physicalDevice = VK_NULL_HANDLE;
            if(instance.instance == VK_NULL_HANDLE){
                        std::cerr << "instance is null\n";
                        throw std::runtime_error("instance is null");
            }
            vkEnumeratePhysicalDevices(instance.instance, &deviceCount, nullptr);
            if(deviceCount == 0){
                        std::cerr << "failed to find GPUs with vulkan support\n";
                        throw std::runtime_error("failed to find GPUs with vulkan support\r\n");
            }
            devices.resize(deviceCount);
            vkEnumeratePhysicalDevices(instance.instance, &deviceCount, devices.data());
            for(size i = 0; i <= devices.size()-1;i++){
                        if(suitable(devices[i])){
                                    physicalDevice = devices[i];
                                    std::cout << physicalDevice << std::endl;
                                    break;
                        }
            }
            if(physicalDevice == VK_NULL_HANDLE){
                        std::cerr << "failed to find suitable GPU\n";
                        throw std::runtime_error("failed to find suitable GPU\r\n");
            }

            std::cout << "device constructor completed!\n";
        }

	bool vkDevice::suitable(VkPhysicalDevice device){
            vkGetPhysicalDeviceProperties(device, &deviceProperties);
            vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
            //return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader; example of possible picking process, also see multimap versin on vulkan tutorial
            return true;

        }

	vkDevice::~vkDevice(){
	}




} //gfx namespace
