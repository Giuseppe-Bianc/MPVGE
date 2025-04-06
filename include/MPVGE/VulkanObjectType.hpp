// clang-format off
// NOLINTBEGIN(*-include-cleaner, *-pro-type-member-init, *-member-init, *-pro-bounds-constant-array-index, *-use-anonymous-namespace, *-pro-type-cstyle-cast, *-pro-type-member-init,*-member-init, *-pro-bounds-constant-array-index, *-qualified-auto, *-uppercase-literal-suffix)
// clang-format on
#pragma once

#include "headers.hpp"

// Primary template: throws if an unsupported Vulkan object type is encountered.
template <typename T> VkObjectType GetVulkanObjectType([[maybe_unused]] T object) {
    throw std::runtime_error("Unsupported Vulkan object type");
}

// ==========================
// VK_VERSION_1_0: Core types
// ==========================
template <> inline VkObjectType GetVulkanObjectType<VkInstance>([[maybe_unused]] VkInstance instance) { return VK_OBJECT_TYPE_INSTANCE; }

template <> inline VkObjectType GetVulkanObjectType<VkPhysicalDevice>([[maybe_unused]] VkPhysicalDevice physicalDevice) {
    return VK_OBJECT_TYPE_PHYSICAL_DEVICE;
}

template <> inline VkObjectType GetVulkanObjectType<VkDevice>([[maybe_unused]] VkDevice device) { return VK_OBJECT_TYPE_DEVICE; }

template <> inline VkObjectType GetVulkanObjectType<VkQueue>([[maybe_unused]] VkQueue queue) { return VK_OBJECT_TYPE_QUEUE; }

template <> inline VkObjectType GetVulkanObjectType<VkSemaphore>([[maybe_unused]] VkSemaphore semaphore) {
    return VK_OBJECT_TYPE_SEMAPHORE;
}

template <> inline VkObjectType GetVulkanObjectType<VkCommandBuffer>([[maybe_unused]] VkCommandBuffer commandBuffer) {
    return VK_OBJECT_TYPE_COMMAND_BUFFER;
}

template <> inline VkObjectType GetVulkanObjectType<VkFence>([[maybe_unused]] VkFence fence) { return VK_OBJECT_TYPE_FENCE; }

template <> inline VkObjectType GetVulkanObjectType<VkDeviceMemory>([[maybe_unused]] VkDeviceMemory memory) {
    return VK_OBJECT_TYPE_DEVICE_MEMORY;
}

template <> inline VkObjectType GetVulkanObjectType<VkBuffer>([[maybe_unused]] VkBuffer buffer) { return VK_OBJECT_TYPE_BUFFER; }

template <> inline VkObjectType GetVulkanObjectType<VkImage>([[maybe_unused]] VkImage image) { return VK_OBJECT_TYPE_IMAGE; }

template <> inline VkObjectType GetVulkanObjectType<VkEvent>([[maybe_unused]] VkEvent eventObj) { return VK_OBJECT_TYPE_EVENT; }

template <> inline VkObjectType GetVulkanObjectType<VkQueryPool>([[maybe_unused]] VkQueryPool queryPool) {
    return VK_OBJECT_TYPE_QUERY_POOL;
}

template <> inline VkObjectType GetVulkanObjectType<VkBufferView>([[maybe_unused]] VkBufferView bufferView) {
    return VK_OBJECT_TYPE_BUFFER_VIEW;
}

template <> inline VkObjectType GetVulkanObjectType<VkImageView>([[maybe_unused]] VkImageView imageView) {
    return VK_OBJECT_TYPE_IMAGE_VIEW;
}

template <> inline VkObjectType GetVulkanObjectType<VkShaderModule>([[maybe_unused]] VkShaderModule shaderModule) {
    return VK_OBJECT_TYPE_SHADER_MODULE;
}

template <> inline VkObjectType GetVulkanObjectType<VkPipelineCache>([[maybe_unused]] VkPipelineCache pipelineCache) {
    return VK_OBJECT_TYPE_PIPELINE_CACHE;
}

template <> inline VkObjectType GetVulkanObjectType<VkPipelineLayout>([[maybe_unused]] VkPipelineLayout pipelineLayout) {
    return VK_OBJECT_TYPE_PIPELINE_LAYOUT;
}

template <> inline VkObjectType GetVulkanObjectType<VkRenderPass>([[maybe_unused]] VkRenderPass renderPass) {
    return VK_OBJECT_TYPE_RENDER_PASS;
}

template <> inline VkObjectType GetVulkanObjectType<VkPipeline>([[maybe_unused]] VkPipeline pipeline) { return VK_OBJECT_TYPE_PIPELINE; }

template <> inline VkObjectType GetVulkanObjectType<VkDescriptorSetLayout>([[maybe_unused]] VkDescriptorSetLayout setLayout) {
    return VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT;
}

template <> inline VkObjectType GetVulkanObjectType<VkSampler>([[maybe_unused]] VkSampler sampler) { return VK_OBJECT_TYPE_SAMPLER; }

template <> inline VkObjectType GetVulkanObjectType<VkDescriptorPool>([[maybe_unused]] VkDescriptorPool descriptorPool) {
    return VK_OBJECT_TYPE_DESCRIPTOR_POOL;
}

template <> inline VkObjectType GetVulkanObjectType<VkDescriptorSet>([[maybe_unused]] VkDescriptorSet descriptorSet) {
    return VK_OBJECT_TYPE_DESCRIPTOR_SET;
}

template <> inline VkObjectType GetVulkanObjectType<VkFramebuffer>([[maybe_unused]] VkFramebuffer framebuffer) {
    return VK_OBJECT_TYPE_FRAMEBUFFER;
}

template <> inline VkObjectType GetVulkanObjectType<VkCommandPool>([[maybe_unused]] VkCommandPool commandPool) {
    return VK_OBJECT_TYPE_COMMAND_POOL;
}

// ==========================
// VK_VERSION_1_1 and VK_VERSION_1_3
// ==========================
template <> inline VkObjectType GetVulkanObjectType<VkSamplerYcbcrConversion>([[maybe_unused]] VkSamplerYcbcrConversion conversion) {
    return VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION;
}

template <>
inline VkObjectType GetVulkanObjectType<VkDescriptorUpdateTemplate>([[maybe_unused]] VkDescriptorUpdateTemplate descriptorUpdateTemplate) {
    return VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE;
}

template <> inline VkObjectType GetVulkanObjectType<VkPrivateDataSlot>([[maybe_unused]] VkPrivateDataSlot slot) {
    return VK_OBJECT_TYPE_PRIVATE_DATA_SLOT;
}

// ==========================
// VK_KHR_surface
// ==========================
#ifdef VK_KHR_surface
template <> inline VkObjectType GetVulkanObjectType<VkSurfaceKHR>([[maybe_unused]] VkSurfaceKHR surface) {
    return VK_OBJECT_TYPE_SURFACE_KHR;
}
#endif

// ==========================
// VK_KHR_swapchain
// ==========================
#ifdef VK_KHR_swapchain
template <> inline VkObjectType GetVulkanObjectType<VkSwapchainKHR>([[maybe_unused]] VkSwapchainKHR swapchain) {
    return VK_OBJECT_TYPE_SWAPCHAIN_KHR;
}
#endif

// ==========================
// VK_KHR_display
// ==========================
#ifdef VK_KHR_display
template <> inline VkObjectType GetVulkanObjectType<VkDisplayKHR>([[maybe_unused]] VkDisplayKHR display) {
    return VK_OBJECT_TYPE_DISPLAY_KHR;
}
template <> inline VkObjectType GetVulkanObjectType<VkDisplayModeKHR>([[maybe_unused]] VkDisplayModeKHR mode) {
    return VK_OBJECT_TYPE_DISPLAY_MODE_KHR;
}
#endif

// ==========================
// VK_EXT_debug_report
// ==========================
#ifdef VK_EXT_debug_report
template <> inline VkObjectType GetVulkanObjectType<VkDebugReportCallbackEXT>([[maybe_unused]] VkDebugReportCallbackEXT callback) {
    return VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT;
}
#endif

// ==========================
// VK_KHR_video_queue
// ==========================
#ifdef VK_KHR_video_queue
template <> inline VkObjectType GetVulkanObjectType<VkVideoSessionKHR>([[maybe_unused]] VkVideoSessionKHR videoSession) {
    return VK_OBJECT_TYPE_VIDEO_SESSION_KHR;
}
template <>
inline VkObjectType GetVulkanObjectType<VkVideoSessionParametersKHR>([[maybe_unused]] VkVideoSessionParametersKHR videoSessionParams) {
    return VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR;
}
#endif

// ==========================
// VK_NVX_binary_import
// ==========================
#ifdef VK_NVX_binary_import
template <> inline VkObjectType GetVulkanObjectType<VkCuModuleNVX>([[maybe_unused]] VkCuModuleNVX cuModule) {
    return VK_OBJECT_TYPE_CU_MODULE_NVX;
}
template <> inline VkObjectType GetVulkanObjectType<VkCuFunctionNVX>([[maybe_unused]] VkCuFunctionNVX cuFunction) {
    return VK_OBJECT_TYPE_CU_FUNCTION_NVX;
}
#endif

// ==========================
// VK_EXT_debug_utils
// ==========================
#ifdef VK_EXT_debug_utils
template <> inline VkObjectType GetVulkanObjectType<VkDebugUtilsMessengerEXT>([[maybe_unused]] VkDebugUtilsMessengerEXT messenger) {
    return VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT;
}
#endif

// ==========================
// VK_KHR_acceleration_structure
// ==========================
#ifdef VK_KHR_acceleration_structure
template <> inline VkObjectType GetVulkanObjectType<VkAccelerationStructureKHR>([[maybe_unused]] VkAccelerationStructureKHR accelStruct) {
    return VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR;
}
#endif

// ==========================
// VK_EXT_validation_cache
// ==========================
#ifdef VK_EXT_validation_cache
template <> inline VkObjectType GetVulkanObjectType<VkValidationCacheEXT>([[maybe_unused]] VkValidationCacheEXT validationCache) {
    return VK_OBJECT_TYPE_VALIDATION_CACHE_EXT;
}
#endif

// ==========================
// VK_NV_ray_tracing
// ==========================
#ifdef VK_NV_ray_tracing
template <> inline VkObjectType GetVulkanObjectType<VkAccelerationStructureNV>([[maybe_unused]] VkAccelerationStructureNV accelStructNV) {
    return VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV;
}
#endif

// ==========================
// VK_INTEL_performance_query
// ==========================
#ifdef VK_INTEL_performance_query
template <>
inline VkObjectType GetVulkanObjectType<VkPerformanceConfigurationINTEL>([[maybe_unused]] VkPerformanceConfigurationINTEL perfConfig) {
    return VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL;
}
#endif

// ==========================
// VK_KHR_deferred_host_operations
// ==========================
#ifdef VK_KHR_deferred_host_operations
template <> inline VkObjectType GetVulkanObjectType<VkDeferredOperationKHR>([[maybe_unused]] VkDeferredOperationKHR deferredOp) {
    return VK_OBJECT_TYPE_DEFERRED_OPERATION_KHR;
}
#endif

// ==========================
// VK_NV_device_generated_commands
// ==========================
#ifdef VK_NV_device_generated_commands
template <>
inline VkObjectType GetVulkanObjectType<VkIndirectCommandsLayoutNV>([[maybe_unused]] VkIndirectCommandsLayoutNV indirectCmdLayout) {
    return VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NV;
}
#endif

// ==========================
// VK_ENABLE_BETA_EXTENSIONS (VK_NV_cuda_kernel_launch)
// ==========================
#ifdef VK_ENABLE_BETA_EXTENSIONS
template <> inline VkObjectType GetVulkanObjectType<VkCuModuleNV>([[maybe_unused]] VkCuModuleNV cuModule) {
    return VK_OBJECT_TYPE_CUDA_MODULE_NV;
}
template <> inline VkObjectType GetVulkanObjectType<VkCuFunctionNV>([[maybe_unused]] VkCuFunctionNV cuFunction) {
    return VK_OBJECT_TYPE_CUDA_FUNCTION_NV;
}
#endif

// ==========================
// VK_FUCHSIA_buffer_collection
// ==========================
#ifdef VK_FUCHSIA_buffer_collection
template <> inline VkObjectType GetVulkanObjectType<VkBufferCollectionFUCHSIA>([[maybe_unused]] VkBufferCollectionFUCHSIA collection) {
    return VK_OBJECT_TYPE_BUFFER_COLLECTION_FUCHSIA;
}
#endif

// ==========================
// VK_EXT_opacity_micromap
// ==========================
#ifdef VK_EXT_opacity_micromap
template <> inline VkObjectType GetVulkanObjectType<VkMicromapEXT>([[maybe_unused]] VkMicromapEXT micromap) {
    return VK_OBJECT_TYPE_MICROMAP_EXT;
}
#endif

// ==========================
// VK_NV_optical_flow
// ==========================
#ifdef VK_NV_optical_flow
template <> inline VkObjectType GetVulkanObjectType<VkOpticalFlowSessionNV>([[maybe_unused]] VkOpticalFlowSessionNV session) {
    return VK_OBJECT_TYPE_OPTICAL_FLOW_SESSION_NV;
}
#endif

// ==========================
// VK_EXT_shader_object
// ==========================
#ifdef VK_EXT_shader_object
template <> inline VkObjectType GetVulkanObjectType<VkShaderEXT>([[maybe_unused]] VkShaderEXT shader) { return VK_OBJECT_TYPE_SHADER_EXT; }
#endif

// ==========================
// VK_NV_external_compute_queue
// ==========================
#ifdef VK_NV_external_compute_queue
template <> inline VkObjectType GetVulkanObjectType<VkExternalComputeQueueNV>([[maybe_unused]] VkExternalComputeQueueNV queue) {
    return VK_OBJECT_TYPE_EXTERNAL_COMPUTE_QUEUE_NV;
}
#endif

// ==========================
// VK_EXT_device_generated_commands (additional)
// ==========================
#ifdef VK_EXT_device_generated_commands
template <> inline VkObjectType GetVulkanObjectType<VkIndirectCommandsLayoutEXT>([[maybe_unused]] VkIndirectCommandsLayoutEXT layout) {
    return VK_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_EXT;
}
template <> inline VkObjectType GetVulkanObjectType<VkIndirectExecutionSetEXT>([[maybe_unused]] VkIndirectExecutionSetEXT set) {
    return VK_OBJECT_TYPE_INDIRECT_EXECUTION_SET_EXT;
}
#endif

// clang-format off
// NOLINTEND(*-include-cleaner, *-pro-type-member-init, *-member-init, *-pro-bounds-constant-array-index, *-use-anonymous-namespace, *-pro-type-cstyle-cast, *-pro-type-member-init,*-member-init, *-pro-bounds-constant-array-index, *-qualified-auto, *-uppercase-literal-suffix)
// clang-format on