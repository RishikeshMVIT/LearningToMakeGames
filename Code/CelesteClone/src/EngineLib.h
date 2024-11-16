#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak();
#endif //Debug Break

#pragma region Logger

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
void _Log(char* prefix, char* msg, TextColor textColor, Args... args)
{
    static char* TextColorTable[TEXT_COLOR_COUNT] = 
    {    
        "\x1b[30m", // TEXT_COLOR_BLACK
        "\x1b[31m", // TEXT_COLOR_RED
        "\x1b[32m", // TEXT_COLOR_GREEN
        "\x1b[33m", // TEXT_COLOR_YELLOW
        "\x1b[34m", // TEXT_COLOR_BLUE
        "\x1b[35m", // TEXT_COLOR_MAGENTA
        "\x1b[36m", // TEXT_COLOR_CYAN
        "\x1b[37m", // TEXT_COLOR_WHITE
        "\x1b[90m", // TEXT_COLOR_BRIGHT_BLACK
        "\x1b[91m", // TEXT_COLOR_BRIGHT_RED
        "\x1b[92m", // TEXT_COLOR_BRIGHT_GREEN
        "\x1b[93m", // TEXT_COLOR_BRIGHT_YELLOW
        "\x1b[94m", // TEXT_COLOR_BRIGHT_BLUE
        "\x1b[95m", // TEXT_COLOR_BRIGHT_MAGENTA
        "\x1b[96m", // TEXT_COLOR_BRIGHT_CYAN
        "\x1b[97m", // TEXT_COLOR_BRIGHT_WHITE
    };

    char formatBuffer[512] = {};
    sprintf(formatBuffer, "%s %s %s \033[0m", TextColorTable[textColor], prefix, msg);

    char textBuffer[512] = {};
    sprintf(textBuffer, formatBuffer, args...);

    puts(textBuffer);    
}

#define ENG_TRACE(msg, ...) _Log("TRACE: ", msg, TEXT_COLOR_GREEN, ##__VA_ARGS__);
#define ENG_WARN(msg, ...) _Log("WARN: ", msg, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define ENG_ERROR(msg, ...) _Log("ERROR: ", msg, TEXT_COLOR_RED, ##__VA_ARGS__);

#define ENG_ASSERT(x, msg, ...)                                             \
{                                                                           \
    if (!(x))                                                               \
    {                                                                       \
        ENG_ERROR(msg, ##__VA_ARGS__);                                      \
        DEBUG_BREAK();                                                      \
    }                                                                       \
}                                                                           \

#pragma endregion

#pragma region Memory

struct BumpAllocator
{
    size_t capacity;
    size_t used;
    char* memory;
};

BumpAllocator MakeBumpAllocator(size_t size)
{
    BumpAllocator ba = {};
    ba.memory = (char*)malloc(size);
    if (ba.memory)
    {
        ba.capacity = size;
        ba.used = 0;
        memset(ba.memory, 0, size);
    }
    else
    {
        ENG_ASSERT(false, "Failed to allocate memory");
    }

    return ba;
}

char* BumpAllocate(BumpAllocator* bumpAllocator, size_t size)
{
    char* result = nullptr;

    size_t alignedSize = (size + 7) & ~ 7;

    if ((bumpAllocator->used + alignedSize) <= bumpAllocator->capacity)
    {
        result = bumpAllocator->memory + bumpAllocator->used;
        bumpAllocator->used += alignedSize;
    }
    else
    {
        ENG_ASSERT(false, "Failed to allocate memory, Bump Allocator is full");
    }

    return result;
}

#pragma endregion

#pragma region File I/O

long long GetTimeStamp(const char* file)
{
    struct stat fileStat = {};
    stat(file, &fileStat);
    return fileStat.st_mtime;
}

long GetFileSize(const char* filePath)
{
    ENG_ASSERT(filePath, "Invalid Path");

    long fileSize = 0;
    auto file = fopen(filePath, "rb");
    if(!file)
    {
      ENG_ERROR("Failed to open file: %s", filePath);
      return 0;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    return fileSize;
}   

bool FileExist(const char* filePath)
{
    ENG_ASSERT(filePath, "Invalid Path");

    auto file = fopen(filePath, "rb");
    if (!file)
    {
        return false;
    }
    
    fclose(file);
}

char* ReadFile(const char* filePath, int* fileSize, char* buffer)
{
    ENG_ASSERT(filePath, "Invalid FilePath");
    ENG_ASSERT(fileSize, "Invalid FileSize");
    ENG_ASSERT(buffer, "Invalid Buffer");

    *fileSize = 0;
    auto file = fopen(filePath, "rb");
    if(!file)
    {
        ENG_ERROR("Failed to open file: %s", filePath);
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

char* ReadFile(const char* filePath, int* fileSize, BumpAllocator* allocator)
{
    char* file = nullptr;
    long fileSize2 = GetFileSize(filePath);

    if(fileSize2)
    {
      char* buffer = BumpAllocate(allocator, fileSize2 + 1);

      file = ReadFile(filePath, fileSize, buffer);
    }

    return file; 
}

void WriteFile(const char* filePath, char* buffer, int size)
{
    ENG_ASSERT(filePath, "Invalid Path");
    ENG_ASSERT(buffer, "Invalid Buffer");

    auto file = fopen(filePath, "wb");
    if(!file)
    {
      ENG_ERROR("Failed to open file: %s", filePath);
      return;
    }

    fwrite(buffer, sizeof(char), size, file);
    fclose(file);
}

bool CopyFile(const char* fileName, const char* outputName, char* buffer)
{
    int fileSize = 0;
    char* data = ReadFile(fileName, &fileSize, buffer);

    auto outputFile = fopen(outputName, "wb");
    if(!outputFile)
    {
        ENG_ERROR("Failed opening File: %s", outputName);
        return false;
    }

    int result = fwrite(data, sizeof(char), fileSize, outputFile);
    if(!result)
    {
        ENG_ERROR("Failed opening File: %s", outputName);
        return false;
    }
    
    fclose(outputFile);

    return true;
}

bool CopyFile(const char* fileName, const char* outputName, BumpAllocator* allocator)
{
  char* file = 0;
  long fileSize2 = GetFileSize(fileName);

  if(fileSize2)
  {
    char* buffer = BumpAllocate(allocator, fileSize2 + 1);

    return CopyFile(fileName, outputName, buffer);
  }

  return false;
}

#pragma endregion