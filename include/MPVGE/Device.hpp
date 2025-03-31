/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "DeviceInfo.hpp"
#include "Instance.hpp"
#include "Surface.hpp"
#include "headers.hpp"

namespace mpvge {

    class Device {
    public:
        Device(Instance &instancein, Surface &surfacein);
        ~Device();
        Device(const Device &) = delete;
        Device &operator=(const Device &) = delete;

        [[nodiscard]] VkDevice get() { return device; }
        [[nodiscard]] VkPhysicalDeviceProperties getProperties() const { return properties; }

    private:
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties properties;
        Surface &surface;
        Instance &instance;
        const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    };

}  // namespace mpvge
