#include <framework/instance.hpp>

fhhengine_status create_instance(const char* application_name,VkInstance* instance)
{
    VkApplicationInfo app_info = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = application_name,
        .applicationVersion = VK_MAKE_VERSION(1,2,0),
        .pEngineName = "FhhEngine",
        .engineVersion = VK_MAKE_VERSION(FHHENGINE_MAJOR_VERSION,
                                         FHHENGINE_MINOR_VERSION,
                                         FHHENGINE_PATCH_VERSION),
        .apiVersion = VK_API_VERSION_1_2
    };

    const char* enable_extension_names[] = {};
    const char* enable_layer_names[] = {};
    VkInstanceCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &app_info,
        .enabledLayerCount      = sizeof(enable_layer_names)/sizeof(const char*),
        .ppEnabledLayerNames    = enable_layer_names,
        .enabledExtensionCount  = sizeof(enable_extension_names)/sizeof(const char*),
        .ppEnabledExtensionNames = enable_extension_names
    };
    VkResult result = vkCreateInstance(&create_info,nullptr,instance);
    if(result!=VK_SUCCESS) {
        return FHHENGINE_GENERIC_FAILURE;
    }
    else {
        return FHHENGINE_SUCCESS;
    }
}
