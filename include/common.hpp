#ifndef COMMON_HPP
#define COMMON_HPP
#include <vulkan/vulkan.hpp>
typedef unsigned long long U64;
typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char U8;

typedef long long I64;
typedef int I32;
typedef short I16;
typedef char I8;

typedef U8 byte;

typedef enum {
    FHHENGINE_SUCCESS=VK_SUCCESS,
    FHHENGINE_GENERIC_FAILURE=-1,
} fhhengine_status;
#endif
