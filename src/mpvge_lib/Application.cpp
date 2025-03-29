/*
* Created by gbian on 29/03/2025.
* Copyright (c) 2025 All rights reserved.
*/

#include "MPVGE/Application.hpp"

namespace mpvge {
    Application::Application() {
        spdlog::info("Application constructor called");
    }

    Application::~Application() {
        spdlog::info("Application destructor called");
    }
} // mpvge