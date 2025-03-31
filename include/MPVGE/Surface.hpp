/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "Instance.hpp"
#include "Window.hpp"
#include "headers.hpp"
#include "vulkanCheck.hpp"

namespace mpvge {

    class Surface {
    public:
        Surface(Instance &instance, Window &window);
        ~Surface();
        Surface(const Surface &) = delete;
        Surface &operator=(const Surface &) = delete;

        VkSurfaceKHR get() const { return surface; }

    private:
        VkSurfaceKHR surface{VK_NULL_HANDLE};
        Instance &instance;
    };

}  // namespace mpvge
