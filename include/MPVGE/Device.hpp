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
        Device(Instance &instancein, Surface &surfacein, bool enableValidationLayersin);
        ~Device();
        Device(const Device &) = delete;
        Device(Device &&) = delete;
        Device &operator=(const Device &) = delete;
        Device &operator=(Device &&) = delete;

        [[nodiscard]] VkDevice getDevice() const noexcept { return device; }
        [[nodiscard]] VkPhysicalDeviceProperties getProperties() const noexcept { return properties; }
        [[nodiscard]] VkCommandPool getCommandPool() const noexcept { return commandPool; }
        [[nodiscard]] VkSurfaceKHR getSurface() const noexcept { return surface.get(); }
        [[nodiscard]] VkQueue getGraphicsQueue() const noexcept { return graphicsQueue; }
        [[nodiscard]] VkQueue getPresentQueue() const noexcept { return presentQueue; }

    private:
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        void createLogicalDevice(const QueueFamilyIndices &indices);
        void createCommandPool(const QueueFamilyIndices &queueFamilyIndices);
        bool enableValidationLayers;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device = VK_NULL_HANDLE;
        VkCommandPool commandPool;
        VkPhysicalDeviceProperties properties;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        Surface &surface;
        Instance &instance;
        const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    };

}  // namespace mpvge
