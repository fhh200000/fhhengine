#include <framework/debug.hpp>
#ifdef FHHENGINE_DEBUG
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                                                     VkDebugUtilsMessageTypeFlagsEXT message_type,
                                                     const VkDebugUtilsMessengerCallbackDataEXT* callback_data, void* user_data)
{
    char message_severity_character='?';
    switch(message_severity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: {message_severity_character='V';break;}
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: {message_severity_character='I';break;}
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: {message_severity_character='W';break;}
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: {message_severity_character='E';break;}
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT: {message_severity_character='?';break;}
    }
    printf("fhhengine [%c] %s\n",message_severity_character,callback_data->pMessage);
    return VK_FALSE;
}

void create_debug_interface(VkInstance* instance, VkDebugUtilsMessengerEXT* messenger)
{
    VkDebugUtilsMessengerCreateInfoEXT debug_info = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                          |VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                          |VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                     | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                     | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = debug_callback,
        .pUserData = nullptr
    };
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*instance,"vkCreateDebugUtilsMessengerEXT");
    if(func!=nullptr) {
        if(func(*instance,&debug_info,nullptr,messenger)!=VK_SUCCESS) {
            printf("Create Debug Fail!\n");
        }
    }
}
void destroy_debug_interface(VkInstance instance, VkDebugUtilsMessengerEXT messenger)
{
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,"vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, messenger, nullptr);
    }
}
#endif
