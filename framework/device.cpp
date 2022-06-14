#include <framework/device.hpp>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
extern const char* enable_extension_names[];
extern const char* enable_layer_names[];
VkPhysicalDevice select_physical_device(VkInstance instance, DeviceRequirement requirements[])
{
    VkPhysicalDevice desired_device;
    U32 device_count;
    VkResult result = vkEnumeratePhysicalDevices(instance,&device_count,nullptr);
    if(result!=VK_SUCCESS) {
        cerr<<"Cannot retrive Vulkan device list!"<<endl;
        return nullptr;
    }
    VkPhysicalDevice* devices = new VkPhysicalDevice[device_count];
    result = vkEnumeratePhysicalDevices(instance,&device_count,devices);
    if(result!=VK_SUCCESS) {
        cerr<<"Cannot retrive Vulkan device list!"<<endl;
        return nullptr;
    }
    VkPhysicalDeviceProperties properties;
    for(int i=0;i<device_count;i++) {
        vkGetPhysicalDeviceProperties(devices[i],&properties);
#ifdef FHHENGINE_DEBUG
        printf("Device #%d: %s ",i,properties.deviceName);
        switch(properties.deviceType) {
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: {printf("(Discrete GPU)\n");break;}
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: {printf("(Integrated GPU)\n");break;}
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: {printf("(Virtual GPU)\n");break;}
            case VK_PHYSICAL_DEVICE_TYPE_CPU: {printf("(CPU)\n");break;}
            case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:
            case VK_PHYSICAL_DEVICE_TYPE_OTHER: {printf("(other)\n");break;}
        }
        printf("Driver version: %d.%d.%d\n",VK_API_VERSION_MAJOR(properties.driverVersion),
                                            VK_API_VERSION_MINOR(properties.driverVersion),
                                            VK_API_VERSION_PATCH(properties.driverVersion));
#endif
    //TODO:DEVICE REQUIREMENTS CALCULATION!
    }
    desired_device = devices[0];
    delete[] devices;
    return desired_device;
}
static U32 get_queue_family_properties(VkPhysicalDevice device, VkQueueFamilyProperties* properties)
{
    U32 status = -1;
    U32 queue_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device,&queue_count,nullptr);
    if(!queue_count) {
        return -1;
    }
    VkQueueFamilyProperties* properties_list = new VkQueueFamilyProperties[queue_count];
    vkGetPhysicalDeviceQueueFamilyProperties(device,&queue_count,properties_list);
    for(U32 i=0;i<queue_count;i++) {
        if(properties_list[i].queueCount>0 && properties_list[i].queueFlags&VK_QUEUE_GRAPHICS_BIT) {
            //Good!
            *properties = properties[i];
            status = i;
            break;
        }
    }
    delete[] properties_list;
    return status;
}
VkDevice create_logical_device(VkPhysicalDevice physical_device)
{
    VkQueueFamilyProperties queue_family_properties;
    VkDevice logical_device;
    U32 queue_family_index = get_queue_family_properties(physical_device,&queue_family_properties);
    if(queue_family_index==-1) {
        cerr<<"Cannot get available queue family!"<<endl;
        return nullptr;
    }
    VkPhysicalDeviceFeatures features = {

    };
    float queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = queue_family_index,
        .queueCount = 1,
        .pQueuePriorities = &queue_priority
    };
    VkDeviceCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queue_create_info,
#ifdef FHHENGINE_DEBUG
        .enabledLayerCount = 1,
        .ppEnabledLayerNames = enable_layer_names,
#else
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
#endif
        .enabledExtensionCount = 0,
        .ppEnabledExtensionNames = nullptr,
        .pEnabledFeatures = &features
    };
    if(vkCreateDevice(physical_device,&create_info,nullptr,&logical_device)!=VK_SUCCESS) {
        cerr<<"Cannot create logical device!"<<endl;
        return nullptr;
    }
    return logical_device;
}
