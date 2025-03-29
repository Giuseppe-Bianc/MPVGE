/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "headers.hpp"

namespace mpvge {
    // Custom deleter for GLFWwindow.
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *window) const {
            if(window) { glfwDestroyWindow(window); }
        }
    };

    // A convenient alias for a unique_ptr managing a GLFWwindow.
    using UniqueGLFWwindow = std::unique_ptr<GLFWwindow, GLFWwindowDeleter>;
    // Helper function that creates a GLFWwindow and wraps it in a unique_ptr.
    UniqueGLFWwindow make_unique_glfw_window(int width, int height, const char *title);
    class Application {
    public:
        Application();
        ~Application();
        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;
        void run();

    private:
        UniqueGLFWwindow window;
    };

}  // namespace mpvge
