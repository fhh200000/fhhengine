#include <framework/frontend.hpp>
#include <framework/instance.hpp>
#include <framework/device.hpp>
#include <framework/surface.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using std::cerr;
using std::endl;

FhhEngine::FhhEngine(U32 width, U32 height, const char* title)
    :width(width),height(height),title(title)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    w = glfwCreateWindow(width,height,title,nullptr,nullptr);
    U32 extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr,&extension_count,nullptr);
    printf("Extensions: %d\n",extension_count);
    fhhengine_status status = create_instance(title,&instance);
    if(status!=FHHENGINE_SUCCESS) {
        cerr<<"Engine creation failed!"<<endl;
        return;
    }
#ifdef FHHENGINE_DEBUG
    create_debug_interface(&instance,&messenger);
#endif
    VkPhysicalDevice physical_device = select_physical_device(instance,nullptr);
    if(physical_device==nullptr) {
        cerr<<"Cannot select a physical device!"<<endl;
        return;
    }
    device = create_logical_device(physical_device);
    if(device==nullptr) {
        cerr<<"Cannot create a logical device!"<<endl;
        return;
    }
    surface = create_surface(instance,w);
    if(surface==nullptr) {
        cerr<<"Cannot create a Surface"<<endl;
        return;
    }
}
void FhhEngine::run()
{
    while(!glfwWindowShouldClose(w)) {
        glfwPollEvents();
    }
}
FhhEngine::~FhhEngine()
{
#ifdef FHHENGINE_DEBUG
    destroy_debug_interface(instance,messenger);
#endif
    destroy_surface(instance,surface);
    vkDestroyDevice(device,nullptr);
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(w);
    glfwTerminate();
}
