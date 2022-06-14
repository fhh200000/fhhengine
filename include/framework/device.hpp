#ifndef DEVICE_HPP
#define DEVICE_HPP
#include <common.hpp>
typedef enum {
    REQUIREMENT_DEVICE_TYPE,
    REQUIREMENT_DEVICE_MEMORY,
    REQUIREMENT_DEVICE_FEATURE
} DeviceRequirementType;
typedef enum {
    REQUIREMENT_DEVICE_TYPE_INTEGRATED_PREFERRED,
    REQUIREMENT_DEVICE_TYPE_INTEGRATED_ONLY,
    REQUIREMENT_DEVICE_TYPE_DISCRETE_PREFERRED,
    REQUIREMENT_DEVICE_TYPE_DISCRETE_ONLY,
} PhysicalDeviceTypeRequirement;
typedef struct {
    DeviceRequirementType type;
    U64                   val;
} DeviceRequirement;
VkPhysicalDevice select_physical_device(VkInstance instance, DeviceRequirement requirements[]);
VkDevice create_logical_device(VkPhysicalDevice physical_device);
#endif
