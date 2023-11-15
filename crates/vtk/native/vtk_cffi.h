#ifndef VTK_CFFI_INCLUDED
#define VTK_CFFI_INCLUDED

#ifdef VTK_RUST_BINDGEN
#include "vtk_cffi_vulkan.h"
typedef void NSApplication;
typedef void VtkViewController;
#else // VTK_RUST_BINDGEN
#include "vulkan_wrapper.h"
#ifdef __APPLE__
#include <Cocoa/Cocoa.h>
#include "vtk_mac.h"
#endif // __APPLE__
#endif // VTK_RUST_BINDGEN

struct VtkApplicationNative {
#ifdef __APPLE__
    /** <div rustbindgen private> */
    NSApplication* ns_application;
#endif
};

struct VtkDeviceNative {
    _Bool initialized;
    VkInstance vk_instance;
    VkPhysicalDevice vk_physical_device;
    VkDevice vk_device;
    uint32_t queue_family_index;
    VkQueue vk_queue;
};

struct VtkWindowNative {
    struct VtkDeviceNative* vtk_device;
    uint32_t width;
    uint32_t height;

    VkSurfaceKHR vk_surface;
    enum VkFormat vk_surface_format;

    VkRenderPass vk_surface_render_pass;
    VkPipelineLayout vk_pipeline_layout;
    VkPipeline vk_pipeline;

    uint8_t num_swap_chain_images;
    VkSwapchainKHR vk_swapchain;
    VkImage* vk_swap_chain_images;
    VkImageView *vk_swap_chain_images_views;
    struct VkExtent2D vk_extent_2d;
    VkFramebuffer *vk_swap_chain_framebuffers;


#ifdef __APPLE__
    /** Platform-specific data. <div rustbindgen private> */
    VtkViewController* vtk_view_controller;
    NSApplication* ns_application;
#endif
};


/** Null-terminated, static string. <div rustbindgen private> */
VkShaderModule vtk_compile_shader(VkDevice vk_device, uint8_t const* bytes, size_t size);

struct VtkApplicationNative* vtk_application_init();

// Run the event loop.
void vtk_application_run(struct VtkApplicationNative* application);

struct VtkDeviceNative* vtk_device_init(struct VtkApplicationNative* vtk_application);

struct VtkWindowNative* vtk_window_init(struct VtkDeviceNative* vtk_device);

#endif