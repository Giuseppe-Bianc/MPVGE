/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#include "MPVGE/Application.hpp"

namespace mpvge {
    UniqueGLFWwindow make_unique_glfw_window(int width, int height, const char *title) {
        // Create the window using GLFW.
        GLFWwindow *rawWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
        return UniqueGLFWwindow(rawWindow);
    }
    Application::Application() {
        LINFO("Application constructor called");
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = make_unique_glfw_window(800, 600, "Vulkan window");
    }
    Application::~Application() {
        glfwTerminate();
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

        while(!glfwWindowShouldClose(window.get())) { glfwPollEvents(); }
    }
}  // namespace mpvge