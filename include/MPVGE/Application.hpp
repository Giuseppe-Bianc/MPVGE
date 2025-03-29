/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "headers.hpp"

namespace mpvge {

    class Application {
    public:
        Application();
        ~Application();
        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;
        void run();
    private:
        GLFWwindow* window;
    };

}  // namespace mpvge
