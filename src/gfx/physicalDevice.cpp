#include "physicalDevice.hpp"


namespace gfx{


	physicalDevice * physicalDevice::get(vkInstance& instance){
            static physicalDevice * device = new physicalDevice(instance);
            return device;
	}

	physicalDevice::physicalDevice(vkInstance& instance) : deviceCount(0), GPU(VK_NULL_HANDLE){
            deviceCount = 0;
            GPU = VK_NULL_HANDLE;
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
                                    GPU = devices[i];
                                    break;
                        }
            }
            if(GPU == VK_NULL_HANDLE){
                        std::cerr << "failed to find suitable GPU\n";
                        throw std::runtime_error("failed to find suitable GPU\r\n");
            }

            printSpecs(GPU);

        }

	bool physicalDevice::suitable(VkPhysicalDevice device){
            vkGetPhysicalDeviceProperties(device, &deviceProperties);
            vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
            //return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader; example of possible picking process, also see multimap versin on vulkan tutorial
            queueFamily foo(device);
            queueFamilyIndices indices = foo.findQueueFamilies(device);
            return indices.isComplete();

        }

            void physicalDevice::printSpecs(VkPhysicalDevice device){
            std::cout << "GPU name: " << deviceProperties.deviceName << "\n";
            std::cout << "API version: " << VK_VERSION_MAJOR(deviceProperties.apiVersion) << "." << VK_VERSION_MINOR(deviceProperties.apiVersion) 
                      << "." << VK_VERSION_PATCH(deviceProperties.apiVersion) << "\n";
            std::cout << "Driver version: " << deviceProperties.driverVersion << "\n";
            std::cout << "Vendor ID: " << deviceProperties.vendorID << "\n";
            std::cout << "Device ID: " << deviceProperties.deviceID << "\n";
            std::cout << "Geometry Shader: " << (deviceFeatures.geometryShader ? "supported" : "not supported") << std::endl;
            }

	physicalDevice::~physicalDevice(){
	}




} //gfx namespace
