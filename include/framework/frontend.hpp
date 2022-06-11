#ifndef FRONTEND_HPP
#define FRONTEND_HPP
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_INCLUDE_VULKAN
#include <common.hpp>
#include <GLFW/glfw3.h>
class FhhEngine {
    private:
        U32 width,height;
        const char* title;
        GLFWwindow* w;
        VkInstance instance;
    public:
        FhhEngine(U32 width, U32 height, const char* title);
        void run();
        ~FhhEngine();
};
#endif
