/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */

#pragma once

/*#include "Device.hpp"
#include "Device.hpp"
#include "Pipeline.hpp"
#include "SwapChain.hpp"*/
#include "headers.hpp"

#include "Instance.hpp"
#include "Surface.hpp"
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
#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else
        const bool enableValidationLayers = true;
#endif
        Window window{wwidth, wheight, wtile};
        Instance instance{wtile.data(), enableValidationLayers};
        Surface surface{instance, window};
        Device device{instance, surface};

        /*Device device{window};
        //Pipeline pipeline{device, calculateRelativePathToShaders(curentP, "simple_shader.vert.opt.rmp.spv").string(),
        //                  calculateRelativePathToShaders(curentP, "simple_shader.frag.opt.rmp.spv").string(),
        Pipeline::defaultPipelineConfigInfo(wwidth, wheight)}; SwapChain lveSwapChain{device, window.getExtent()}; std::unique_ptr<Pipeline>
        pipeline; VkPipelineLayout pipelineLayout; std::vector<VkCommandBuffer> commandBuffers;*/
    };

}  // namespace mpvge
