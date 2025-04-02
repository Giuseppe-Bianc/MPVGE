/*
* Created by gbian on 02/04/2025.
* Copyright (c) 2025 All rights reserved.
*/

#include "../../include/MPVGE/RenderPipeline.hpp"

namespace mpvge {

    RenderPipeline::RenderPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
        createGraphicsPipeline(vertFilepath, fragFilepath);
    }

    std::vector<char> RenderPipeline::readFile(const std::string& filepath) {
        std::ifstream file{filepath, std::ios::ate | std::ios::binary};

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file: " + filepath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();
        return buffer;
    }

    void RenderPipeline::createGraphicsPipeline(
        const std::string& vertFilepath, const std::string& fragFilepath) {
        auto vertCode = readFile(vertFilepath);
        auto fragCode = readFile(fragFilepath);

      LINFO("Vertex Shader Code Size: {}",vertCode.size());
      LINFO("Fragment Shader Code Size: {}",fragCode.size());
    }
} // mpvge