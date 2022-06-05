#include <common.hpp>
#include <framework/frontend.hpp>

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900

int main(int argc, char *argv[])
{
    FhhEngine engine(1440,900,"Vulkan Test");
    engine.run();
}
