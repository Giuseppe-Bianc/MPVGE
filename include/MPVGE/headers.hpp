/*
 * Created by gbian on 29/03/2025.
 * Copyright (c) 2025 All rights reserved.
 */
// // NOLINTBEGIN(*-include-cleaner)
#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <mpvge_lib_core/mpvge_lib_core.hpp>

DISABLE_WARNINGS_PUSH(26426)
static inline constexpr std::string_view wtile = MPVGE::cmake::project_name;
// static inline constexpr std::size_t factor = 80;
// static inline constexpr auto wfactor = 16;
// static inline constexpr auto hfactor = 9;
static inline constexpr std::size_t factor = 200;
static inline constexpr auto wfactor = 4;
static inline constexpr auto hfactor = 3;
static inline constexpr auto wwidth = wfactor * factor;
static inline constexpr auto wheight = hfactor * factor;
static inline constexpr auto aspectRatio = C_D(wfactor) / C_D(hfactor);
static inline constexpr auto aspectRatiof = C_F(wfactor) / C_F(hfactor);
static inline constexpr auto ui32tmax = C_UI32T(std::numeric_limits<uint32_t>::max());
static inline constexpr auto uint64Max = C_UI64T(std::numeric_limits<uint64_t>::max());
static inline constexpr auto fepsilon = std::numeric_limits<float>::epsilon();
static inline constexpr auto glm2pi = glm::two_pi<float>();
static inline const auto curentP = fs::current_path();
static inline const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};
DISABLE_WARNINGS_POP()

[[nodiscard]] static constexpr auto calcolaCentro(const int &width, const int &w) noexcept { return (width - w) / 2; }
#define CALC_CENTRO(width, w) calcolaCentro(width, w)

inline fs::path calculateRelativePathToSrc(const fs::path &executablePath, const fs::path &targetFile, const std::string &subDir) {
    fs::path parentDir = executablePath.parent_path();
    while(!fs::exists(parentDir / "src")) {
        parentDir = parentDir.parent_path();
        if(parentDir == parentDir.root_path()) {
            LERROR("Error: 'src' directory not found in the path.");
            return {};
        }
    }
    parentDir = parentDir.parent_path();
    const auto resp = fs::path(subDir);
    const auto relativePathToTarget = parentDir / resp / targetFile;
    const auto relativePath = fs::relative(relativePathToTarget, executablePath);
    return relativePath.lexically_normal();
}

inline fs::path calculateRelativePathToShaders(const fs::path &executablePath, const fs::path &targetFile) {
    return calculateRelativePathToSrc(executablePath, targetFile, "shaders");
}
inline fs::path calculateRelativePathToTextures(const fs::path &executablePath, const fs::path &targetFile) {
    return calculateRelativePathToSrc(executablePath, targetFile, "textures");
}
inline fs::path calculateRelativePathToModels(const fs::path &executablePath, const fs::path &targetFile) {
    return calculateRelativePathToSrc(executablePath, targetFile, "models");
}

#define DESTROY_VK_HANDLE(handle, destroy_call)                                                                                            \
    if((handle) != VK_NULL_HANDLE) {                                                                                                       \
        destroy_call;                                                                                                                      \
        (handle) = VK_NULL_HANDLE;                                                                                                         \
    }

// NOLINTEND(*-include-cleaner)