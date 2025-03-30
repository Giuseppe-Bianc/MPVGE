/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#include "MPVGE/Application.hpp"

namespace mpvge {
    Application::Application() {
        LINFO("Application constructor called");
    }
    Application::~Application() {
        LINFO("Application destructor called");
    }
    void Application::run() {
        LINFO("Application run called");
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported\n";

        glm::mat4 matrix;
        glm::vec4 vec;
        auto test = matrix * vec;

        while(!window.shouldClose()) {
            glfwPollEvents();
        }
    }
}  // namespace mpvge