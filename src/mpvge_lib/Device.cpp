/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// NOLINTBEGIN(*-include-cleaner)
#include "MPVGE/Device.hpp"

namespace mpvge {
    static inline constexpr float queuePriority = 1.0f;

    Device::Device(Instance &instancein, Surface &surfacein, bool enableValidationLayersin)
      : enableValidationLayers{enableValidationLayersin}, surface{surfacein}, instance{instancein} {
        pickPhysicalDevice();
        const QueueFamilyIndices indices = surface.getQueueFamilyIndices(physicalDevice);
        createLogicalDevice(indices);
        LINFO("Device created");
        createCommandPool(indices);
        LINFO("Command pool created");
    }

    Device::~Device() {
        DESTROY_VK_HANDLE(commandPool, vkDestroyCommandPool(device, commandPool, nullptr));
        LINFO("Command pool destroyed");
        DESTROY_VK_HANDLE(physicalDevice, vkDestroyDevice(device, nullptr));
        LINFO("Device destroyed");
    }

    void Device::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance.get(), &deviceCount, nullptr);
        if(deviceCount == 0) { throw std::runtime_error("failed to find GPUs with Vulkan support!"); }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance.get(), &deviceCount, devices.data());

        std::size_t deviceIndex = 0;
        for(const auto &[index, pdevice] : devices | std::views::enumerate) {
            if(isDeviceSuitable(pdevice)) {
                physicalDevice = pdevice;
                deviceIndex = index;
                break;
            }
        }
        if(physicalDevice == VK_NULL_HANDLE) { throw std::runtime_error("failed to find a suitable GPU!"); }
        vkGetPhysicalDeviceProperties(physicalDevice, &properties);
        VLINFO("Device index: {}", deviceIndex);
        printDeviceInfo(physicalDevice, properties);
    }

    bool Device::isDeviceSuitable(VkPhysicalDevice devicein) {
        QueueFamilyIndices indices = surface.getQueueFamilyIndices(devicein);
        const bool extensionsSupported = checkDeviceExtensionSupport(devicein);
        bool swapChainAdequate = false;
        if(extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = surface.querySwapChainSupport(devicein);
            swapChainAdequate = swapChainSupport.isAdequate();
        }

        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(devicein, &supportedFeatures);
        return indices.is_complete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }

    bool Device::checkDeviceExtensionSupport(VkPhysicalDevice devicein) {
        uint32_t extensionCount{};
        vkEnumerateDeviceExtensionProperties(devicein, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(devicein, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for(const auto &extension : availableExtensions) {
            // NOLINTNEXTLINE(*-pro-bounds-array-to-pointer-decay, *-no-array-decay)
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    void Device::createLogicalDevice(const QueueFamilyIndices &indices) {
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphics_family(), indices.present_family()};

        for(const uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = C_UI32T(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = C_UI32T(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        // might not really be necessary anymore because device specific validation layers
        // have been deprecated
#ifdef NDEBUG
        if(enableValidationLayers) [[unlikely]] {
            createInfo.enabledLayerCount = NC_UI32T(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else [[likely]] {
            createInfo.enabledLayerCount = 0;
        }
#else
        if(enableValidationLayers) [[likely]] {
            createInfo.enabledLayerCount = NC_UI32T(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else [[unlikely]] {
            createInfo.enabledLayerCount = 0;
        }
#endif

        VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device), "failed to create logical device!");
    }

    void Device::createCommandPool(const QueueFamilyIndices &queueFamilyIndices) {
        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphics_family();
        poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        VK_CHECK(vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool), "failed to create command pool!");
    }
}  // namespace mpvge

// NOLINTEND(*-include-cleaner)