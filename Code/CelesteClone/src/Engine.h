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
#include <sys/stat.h>

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

namespace File
{

long long GetTimeStamp(char* file)
{
    struct stat fileStat = {};
    stat(file, &fileStat);
    return fileStat.st_mtime;
}

bool FileExists(char* filePath)
{
    CE_ASSERT(filePath, "No file path");

    auto file = fopen(filePath, "rb");
    if (!file)
        return false;
    fclose(file);
    return true;
}

long GetFileSize(char* filePath)
{
    CE_ASSERT(filePath, "No  file path");

    long fileSize = 0;
    auto file = fopen(filePath, "rb");
    if (!file)
    {
        CE_ERROR("Faield to open file: %s", filePath);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    return fileSize;
}

char* ReadFile(char* filePath, int* fileSize, char* buffer)
{
    CE_ASSERT(filePath, "No file path");
    CE_ASSERT(fileSize, "No file size");

    *fileSize = 0;
    auto file = fopen(filePath, "rb");
    if (!file)
    {
        CE_ERROR("Failed to open file: %s", filePath);
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    *fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    memset(buffer, 0, *fileSize + 1);
    fread(buffer, sizeof(char), *fileSize, file);

    fclose(file);

    return buffer;
}

char* ReadFile(char* filePath, int* fileSize, BumpAllocator* allocator)
{
    char* file = nullptr;
    long size = GetFileSize(filePath);

    if (size)
    {
        char * buffer = BumpAlloc(allocator, size + 1);
        file = ReadFile(filePath, fileSize, buffer);
    }

    return file;
}

void WriteFile(char* filePath, char* buffer, int size)
{
    CE_ASSERT(filePath, "No file path");
    CE_ASSERT(buffer, "No buffer");

    auto file = fopen(filePath, "wb");
    if (!file)
    {
        CE_ERROR("Faield to open file: %s", filePath);
        return;
    }

    fwrite(buffer, sizeof(char), size, file);
    fclose(file);
}

bool CopyFile(char* filePath, char* outputName, char* buffer)
{
    int fileSize = 0;
    char* data = ReadFile(filePath, &fileSize, buffer);

    auto outputFile = fopen(outputName, "wb");
    if(!outputFile)
    {
        CE_ERROR("Faield t oopen file: %s", outputName);
        return false;
    }

    int result = fwrite(data, sizeof(char), fileSize, outputFile);
    if(!result)
    {
        CE_ERROR("Faield writing to file: %s", outputName);
        return false;
    }

    fclose(outputFile);
    return true;
}

bool CopyFile(char* filePath, char* outputName, BumpAllocator* allocator)
{
    char* file = nullptr;
    long fileSize = GetFileSize(filePath);

    if(fileSize)
    {
        char* buffer = BumpAlloc(allocator, fileSize + 1);
        return CopyFile(filePath, outputName, buffer);
    }

    return true;
}
}