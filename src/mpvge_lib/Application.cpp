/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#include "MPVGE/Application.hpp"

namespace mpvge {
    Application::Application() {}
    Application::~Application() {}

    void Application::run() {
        LINFO("Application run called");
        while(!window.shouldClose()) { glfwPollEvents(); }
    }
}  // namespace mpvge