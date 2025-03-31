/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// NOLINTBEGIN(*-include-cleaner)
#include "Device.hpp"

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
        LINFO("found {} devices", deviceCount);
    }

}  // namespace mpvge

// NOLINTEND(*-include-cleaner)