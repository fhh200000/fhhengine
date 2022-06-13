#include <framework/device.hpp>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
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
