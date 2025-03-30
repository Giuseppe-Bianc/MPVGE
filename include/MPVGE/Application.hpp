/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

#include "headers.hpp"

#include "Window.hpp"

namespace mpvge {
    class Application {
    public:
        Application();
        ~Application();
        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;
        void run();

    private:
        Window window{wwidth, wheight, wtile};
    };

}  // namespace mpvge
