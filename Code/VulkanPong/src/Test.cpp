#include <iostream>
#include <stdexcept>
#include <vector>

#define WIN32_LEAN_AND_MEAN

#include <vulkan/vulkan.h>
#include <Windows.h>

static LRESULT OnWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

HWND IntializeWindow()
{
    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(wcex);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = OnWindowMessage;
    wcex.cbClsExtra;
    wcex.cbWndExtra;
    wcex.hInstance;
    wcex.hIcon;
    wcex.hCursor;
    wcex.hbrBackground;
    wcex.lpszMenuName;
    wcex.lpszClassName;
    /* Win 4.0 */
    wcex.hIconSm;
    ATOM windowClass = RegisterClassExW(&wcex);

    if (!windowClass)
        throw std::runtime_error("Failed to register window");

    HWND windowHandle = CreateWindowExW(
        WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW,
        (LPCWSTR)windowClass,
        L"Main Window",
        WS_OVERLAPPEDWINDOW | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        960, 540,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    if (!windowHandle)
        throw std::runtime_error("Failed to create window");
    
    return windowHandle;
}
void ShutdownWindow()
{
    //DestroyWindow(hWnd);
    //UnregisterClassW((LPCWSTR)windowClass, nullptr);
}

//Debug Messenger Creation
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* debugMessengerInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* debugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
        return func(instance, debugMessengerInfo, pAllocator, debugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

int main()
{
    VkInstance instance;

    const uint32_t width = 960;
    const uint32_t height = 540;

    const std::vector<const char*> layers = {"VK_LAYER_KHRONOS_validation"};
    uint32_t layerCount = layers.size();

    const std::vector<const char*> extensions = {};
    uint32_t extensionCount = extensions.size();

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "Vulkan Render";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Vulkan Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pNext = nullptr;
    instanceInfo.flags = NULL;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledLayerCount = layerCount;
    instanceInfo.ppEnabledLayerNames = layers.data();
    instanceInfo.enabledExtensionCount = extensionCount;
    instanceInfo.ppEnabledExtensionNames = extensions.data();

    if (vkCreateInstance(&instanceInfo, nullptr, &instance))
        
}

int array[10] = {}