/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// // NOLINTBEGIN(*-include-cleaner)
#include "MPVGE/Instance.hpp"

#include "MPVGE/VulkanLogInfoCallback.hpp"

namespace mpvge {
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                        [[maybe_unused]] void *pUserData) {
#ifdef INDEPTH
        vnd::AutoTimer t{"Debug Callback", vnd::Timer::Big};
#endif
        // Determine the message type
        const std::string type = VkDebugUtilsMessageTypeFlagsEXTString(messageType);

        // Format and log the message
        const auto msg = FORMAT("{}Message ID: {}({}): {}", type, pCallbackData->pMessageIdName ? pCallbackData->pMessageIdName : "Unknown",
                                pCallbackData->messageIdNumber, pCallbackData->pMessage);

        printMessageWhitSeverity(msg, messageSeverity);

        logDebugValidationLayerInfo(pCallbackData, messageSeverity);

        return VK_FALSE;
    }

    bool Instance::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for(const char *layerName : validationLayers) {
            bool layerFound = false;
            for(const auto &layerProperties : availableLayers) {
                if(strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }
            if(!layerFound) {
                std::cerr << "Validation layer " << layerName << " not supported!" << std::endl;
                return false;
            }
        }
        return true;
    }

    Instance::Instance(const char *appName, bool enableValidationLayersin) : enableValidationLayers(enableValidationLayersin) {
        createInstance(appName);
        setupDebugMessenger();
        LINFO("Instance created");
    }

    Instance::~Instance() {
        if(enableValidationLayers) {
            if(debugMessenger != VK_NULL_HANDLE) {
                DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
                debugMessenger = VK_NULL_HANDLE;
            }
            LINFO("Debug messenger destroyed");
        }
        if(instance != VK_NULL_HANDLE) {
            vkDestroyInstance(instance, nullptr);
            instance = VK_NULL_HANDLE;
        }
        LINFO("Instance destroyed");
    }
    void Instance::createInstance(const char *app_name) {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = app_name;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if(enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.ppEnabledLayerNames = nullptr;
        }

        if(enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("Validation layers requested but not available!");
        }

        VK_CHECK(vkCreateInstance(&createInfo, nullptr, &instance), "Failed to create instance");
        hasGflwRequiredInstanceExtensions();
    }

    std::vector<const char *> Instance::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if(enableValidationLayers) { extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME); }
        return extensions;
    }

    void Instance::setupDebugMessenger() {
        if(!enableValidationLayers) return;

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;

        VK_CHECK(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger), "Failed to set up debug messenger!");
    }

    VkResult Instance::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                                    const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger) {
        auto func = std::bit_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
        if(func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    void Instance::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                                 const VkAllocationCallbacks *pAllocator) {
        auto func = std::bit_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
        if(func != nullptr) { func(instance, debugMessenger, pAllocator); }
    }

    void Instance::hasGflwRequiredInstanceExtensions() {
#ifdef INDEPTH
        vnd::AutoTimer t{"hasGflwRequiredInstanceExtensions", vnd::Timer::Big};
#endif
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::unordered_set<std::string_view> available;
        available.reserve(extensionCount);  // Riserviamo spazio per migliorare le prestazioni

#if defined(_DEBUG) || defined(DEBUG)
        std::vector<std::string> availableExtensions;
#endif
        available.reserve(extensionCount);
        for(const auto &[extensionName, specVersion] : extensions) {
#if defined(_DEBUG) || defined(DEBUG)
            availableExtensions.emplace_back(FORMAT("{} (v. {})", extensionName, specVersion));
#endif
            available.emplace(extensionName);
        }

        const auto requiredExtensions = getRequiredExtensions();
        if(!std::ranges::all_of(requiredExtensions, [&](const auto &required) { return available.contains(required); })) [[unlikely]] {
            throw std::runtime_error("Missing required GLFW extension");
        }
#ifdef NDEBUG
        VLINFO("available extensions count: {}", available.size());
        VLINFO("required extensions count: {}", requiredExtensions.size());
#else
        VLINFO("available extensions:\n  {}", FMT_JOIN(availableExtensions, "\n  "));
        VLINFO("required extensions:\n  {}", FMT_JOIN(requiredExtensions, "\n  "));
#endif
    }
}  // namespace mpvge

// NOLINTEND(*-include-cleaner)