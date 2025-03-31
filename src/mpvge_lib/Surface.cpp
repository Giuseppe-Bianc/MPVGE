/*
 * Created by gbian on 31/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// // NOLINTBEGIN(*-include-cleaner)
#include "MPVGE/Surface.hpp"

namespace mpvge {
    Surface::Surface(Instance &instancein, Window &window) : instance{instancein} {
        window.createWindowSurface(instance.get(), &surface);
        LINFO("Surface created");
    }
    Surface::~Surface() {
        if(surface != VK_NULL_HANDLE) {
            vkDestroySurfaceKHR(instance.get(), surface, nullptr);
            surface = VK_NULL_HANDLE;
        }
        LINFO("Surface destroyed");
    }

}  // namespace mpvge

// NOLINTEND(*-include-cleaner)
