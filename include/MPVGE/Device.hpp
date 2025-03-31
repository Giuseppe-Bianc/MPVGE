/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

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

    private:
        void pickPhysicalDevice();
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device = VK_NULL_HANDLE;
        Surface &surface;
        Instance &instance;
    };

}  // namespace mpvge
