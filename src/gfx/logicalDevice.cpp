#include "logicalDevice.hpp"


namespace gfx{
            logicalDevice * logicalDevice::get(physicalDevice& GPU, vkInstance& instance){
                        logicalDevice * device = new logicalDevice(GPU, instance);
                        return device;
            }

            logicalDevice::logicalDevice(physicalDevice& GPU, vkInstance& instance){
                        queueFamily foo(GPU.GPU);
                        indices = foo.findQueueFamilies(GPU.GPU);
                        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
                        queueCreateInfo.queueCount = 1;
                        queuePriority = 1.0f;
                        queueCreateInfo.pQueuePriorities = &queuePriority;
                        queueCreateInfo.pNext = NULL;


                        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                        createInfo.pQueueCreateInfos = &queueCreateInfo;
                        createInfo.queueCreateInfoCount = 1;
                        createInfo.pEnabledFeatures = &deviceFeatures;
                        createInfo.pNext = NULL;

                        createInfo.enabledExtensionCount = 0;
                        #ifndef NDEBUG
                                    createInfo.enabledLayerCount = (u32)instance.validationLayers.size();
                                    createInfo.ppEnabledLayerNames = instance.validationLayers.data();
                        #else
                                    createInfo.enabledLayerCount = 0;
                        #endif

                        if(vkCreateDevice(GPU.GPU, &createInfo, nullptr,&device) != VK_SUCCESS){
                                    std::cerr << "failed to create logical device\n";
                                    throw std::runtime_error("failed to create logical device\n");
                        }
                        
                        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
                        
            }
            logicalDevice::~logicalDevice(){
                        vkDestroyDevice(device, nullptr);
            }

} // gfx namespace
