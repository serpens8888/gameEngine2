#include "queue.hpp"


            size i = 0;

namespace gfx{

            queueFamily::queueFamily(VkPhysicalDevice GPU){

            }

            queueFamilyIndices queueFamily::findQueueFamilies(VkPhysicalDevice device){
                        queueFamilyIndices indices;
		        queueFamilyCount = 0;
                        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
                        queueFamilies.resize(queueFamilyCount);
                        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
                        
                        size i = 0;
                        for(const auto& family : queueFamilies){
                                    if(family.queueFlags & VK_QUEUE_GRAPHICS_BIT){
                                                indices.graphicsFamily = i;
                                    }
                                    
                                    if(indices.isComplete()){
                                                break;
                                    }
                                    i++;
                        }

                        return indices;

            }

            queueFamily::~queueFamily(){
                        
            }



            bool queueFamilyIndices::isComplete(){
                        return graphicsFamily.has_value();
            }

} //gfx namespace
