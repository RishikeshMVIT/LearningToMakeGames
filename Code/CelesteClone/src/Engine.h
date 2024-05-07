#pragma once

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#elif __linux__
#define DEBUG_BREAK() __builtin_debugtrap()
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TextColor
{
    TEXT_COLOR_BLACK,
    TEXT_COLOR_RED,
    TEXT_COLOR_GREEN,
    TEXT_COLOR_YELLOW,
    TEXT_COLOR_BLUE,
    TEXT_COLOR_MAGENTA,
    TEXT_COLOR_CYAN,
    TEXT_COLOR_WHITE,
    TEXT_COLOR_BRIGHT_BLACK,
    TEXT_COLOR_BRIGHT_RED,
    TEXT_COLOR_BRIGHT_GREEN,
    TEXT_COLOR_BRIGHT_YELLOW,
    TEXT_COLOR_BRIGHT_BLUE,
    TEXT_COLOR_BRIGHT_MAGENTA,
    TEXT_COLOR_BRIGHT_CYAN,
    TEXT_COLOR_BRIGHT_WHITE,
    TEXT_COLOR_COUNT
};

template <typename ...Args>
void _Log(char * prefix, char * msg, TextColor textColor, Args... args)
{
    static char * TextColorTable[TEXT_COLOR_COUNT] ={
        "\x1b[30m",
        "\x1b[31m",
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[34m",
        "\x1b[35m",
        "\x1b[36m",
        "\x1b[37m",
        "\x1b[90m",
        "\x1b[91m",
        "\x1b[92m",
        "\x1b[93m",
        "\x1b[94m",
        "\x1b[95m",
        "\x1b[96m",
        "\x1b[97m"
    };

    char formatBuffer[512] = {};
    sprintf(formatBuffer, "%s %s %s \033[0m", TextColorTable[textColor], prefix, msg);

    char textBuffer[512] = {};
    sprintf(textBuffer, formatBuffer, args...);

    puts(textBuffer);
}

#define CE_TRACE(msg, ...) _Log("TRACE: ", msg, TEXT_COLOR_GREEN,  ##__VA_ARGS__);
#define CE_WARN(msg, ...)  _Log("WARN: ",  msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define CE_ERROR(msg, ...) _Log("ERROR: ", msg, TEXT_COLOR_RED,    ##__VA_ARGS__);

#define CE_ASSERT(x, msg, ...)          \
{                                       \
    if (!(x))                           \
    {                                   \
        CE_ERROR(msg, ##__VA_ARGS__);   \
        DEBUG_BREAK();                  \
    }                                   \
}

struct BumpAllocator
{
    size_t capacity;
    size_t used;
    char* memory;
};

BumpAllocator MakeAllocator(size_t size)
{
    BumpAllocator allocator = {};
    allocator.memory = (char* )malloc(size);

    if (!allocator.memory)
        CE_ASSERT(false, "Failed to allocate memory");

    memset(allocator.memory, 0, size);
    allocator.used = 0;
    allocator.capacity = size;

    return allocator;
}

char* BumpAlloc(BumpAllocator* allocator, size_t size)
{
    char* result = nullptr;
    size_t alignedSize = (size + 7) & ~7;

    if (allocator->used + alignedSize <= allocator->capacity)
    {
        result = allocator->memory + allocator->used;
        allocator->used += alignedSize;
    }
    else
    {
        CE_ASSERT(false, "BumpAllocator is full");
    }

    return result;
}