#include <framework/frontend.hpp>
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
}
void FhhEngine::run()
{
    while(!glfwWindowShouldClose(w)) {
        glfwPollEvents();
    }
    glfwDestroyWindow(w);
}

