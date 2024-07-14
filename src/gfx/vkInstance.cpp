#include "vkInstance.hpp"



namespace gfx{

            vkInstance * vkInstance::get(){
                        static vkInstance* instance = new vkInstance();
                        return instance;
                        
            }

            bool vkInstance::layerCheck(const std::vector<const char*>& layers, const std::vector<VkLayerProperties>& available){
                        for(size i = 0;i<layers.size()-1;i++){
                                    bool layerFound = false;
                                    for(size j = 0;j<available.size()-1;j++){
                                                if(strcmp(layers[i], available[j].layerName) == 0){
                                                            layerFound = true;
                                                            break;
                                                }
                                    }
                                    if(!layerFound){
                                                return false;
                                    }
                        }
                        return true;

            }

            vkInstance::vkInstance(){
                        #ifdef NDEBUG
                                    const bool enableValidationLayers = false;
                        #else
                                    const bool enableValidationLayers = true;
                                    validationLayers = { "VK_LAYER_KHRONOS_validation" };
                                    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
                                    availableLayers.reserve(layerCount);
                                    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
                                    if(!layerCheck(validationLayers, availableLayers)){
                                                std::cerr << "validation layer requested but not available: \n";
                                    }
                        #endif

                        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                        appInfo.pApplicationName = "alchemy";
                        appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
                        appInfo.pEngineName = "my game engine";
                        appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
                        appInfo.apiVersion = VK_API_VERSION_1_3;

                        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                        createInfo.pApplicationInfo = &appInfo;
                        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
                        if(enableValidationLayers){
                                    createInfo.enabledLayerCount = (u32)validationLayers.size();;
                                    createInfo.ppEnabledLayerNames = validationLayers.data();
                                    for (int i = 0; i < glfwExtensionCount; ++i) {
                                                extensions.push_back(glfwExtensions[i]);
                                    }
                                    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
                                    createInfo.enabledExtensionCount = (u32)extensions.size();
                                    createInfo.ppEnabledExtensionNames = (const char**)extensions.data();
                        }
                        else{
                        createInfo.enabledLayerCount = 0;
                        createInfo.enabledExtensionCount = glfwExtensionCount;
                        createInfo.ppEnabledExtensionNames = glfwExtensions;
                        }

                        debugCreateInfo.pNext = NULL; // makes the validation layers happy if i set it to null before making the instance
                        createInfo.pNext = NULL;
                        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
                                    throw std::runtime_error("failed to create instance");
                        }

                        printExtensions();

                        if(enableValidationLayers){
                                    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                                    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                                                      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
                                    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                                                                  | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
                                    debugCreateInfo.pfnUserCallback = debugCallback;
                                    debugCreateInfo.pUserData = nullptr;

                                    if(CreateDebugUtilsMessengerEXT(instance, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS){
                                                throw std::runtime_error("failed to set up debug messenger");
                                    }
                        }

            }

            VKAPI_ATTR VkBool32 VKAPI_CALL vkInstance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* userData){
                        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
                        return VK_FALSE;
            }

            VkResult vkInstance::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
				              const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger){
                        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
                        if (func != nullptr) {
                                    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
                        } else {
                                    return VK_ERROR_EXTENSION_NOT_PRESENT;
                        }
            }

            void vkInstance::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator){
                        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
                        if (func != nullptr) {
                                    func(instance, debugMessenger, pAllocator);
                        }
            }

            void vkInstance::printExtensions(){
                        u32 extCount = 0;
                        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
                        std::vector<VkExtensionProperties> extensionsList(extCount);
                        vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extensionsList.data());

                        std::cout << "available vulkan extensions: \n";
                        for(const auto& extension : extensionsList){
                                    std::cout << "\t" << extension.extensionName << "\n";
                        }

            }
            vkInstance::~vkInstance(){
                        #ifndef NDEBUG
                                   DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
                        #endif

                        vkDestroyInstance(instance, nullptr);
            }



} //namespce gfx
