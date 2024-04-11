#include <iostream>
#include <vector>

#include <vulkan/vulkan.h>
#include <Windows.h>

int main()
{

}

class Renderer
{
public:
    void Initialize()
    {
        VkApplicationInfo vkAppInfo = {};
        vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        vkAppInfo.pNext = nullptr;
        vkAppInfo.pApplicationName = "Whoop";
        vkAppInfo.applicationVersion = 0;
        vkAppInfo.pEngineName = "No Engine";
        vkAppInfo.engineVersion;
        vkAppInfo.apiVersion;

        VkInstanceCreateInfo vkInstanceInfo = {};
        vkInstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        vkInstanceInfo.pNext = nullptr;
        //vkInstanceInfo.flags;
        vkInstanceInfo.pApplicationInfo = &vkAppInfo;
        //vkInstanceInfo.enabledLayerCount;
        //vkInstanceInfo.ppEnabledLayerNames;
        //vkInstanceInfo.enabledExtensionCount;
        //vkInstanceInfo.ppEnabledExtensionNames;

        vkCreateInstance(&vkInstanceInfo, nullptr, &instance);
    }

private:

    VkInstance instance;
    VkDevice device;
};