#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <common.hpp>
void create_debug_interface(VkInstance* instance, VkDebugUtilsMessengerEXT* messenger);
void destroy_debug_interface(VkInstance instance, VkDebugUtilsMessengerEXT messenger);
#endif
