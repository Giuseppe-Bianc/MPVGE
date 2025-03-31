/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// NOLINTBEGIN(*-include-cleaner)
#include "../../include/MPVGE/Device.hpp"

namespace mpvge {
    Device::Device(Instance &instancein, Surface &surfacein) : instance{instancein}, surface{surfacein} {
        pickPhysicalDevice();
        LINFO("Device created");
    }

    Device::~Device() {
        if(device != VK_NULL_HANDLE) {
            vkDestroyDevice(device, nullptr);
            device = VK_NULL_HANDLE;
        }
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

}  // namespace mpvge

// NOLINTEND(*-include-cleaner)