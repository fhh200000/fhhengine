#include <framework/frontend.hpp>
#include <framework/instance.hpp>
#include <cstdio>
#include <cstdlib>

FhhEngine::FhhEngine(U32 width, U32 height, const char* title)
    :width(width),height(height),title(title)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    w = glfwCreateWindow(width,height,title,nullptr,nullptr);
    U32 extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr,&extension_count,nullptr);
    printf("Extensions:%d\n",extension_count);
    fhhengine_status status = create_instance(title,&instance);
    if(status!=FHHENGINE_SUCCESS) {
        printf("Engine creation failed!\n");
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
    glfwDestroyWindow(w);
    glfwTerminate();
}
