#include "Renderer.h"

const char* TEXTURE_PATH = "assets/textures/TextureAtlas.png";

struct GLContext
{
    GLuint program;
    GLuint texture;
};

static GLContext glContext;

static void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint ID, GLenum severity, GLsizei length, const GLchar* message, const void* user)
{
    if (
        severity == GL_DEBUG_SEVERITY_LOW ||
        severity == GL_DEBUG_SEVERITY_MEDIUM ||
        severity == GL_DEBUG_SEVERITY_HIGH
        )
    {   CE_ASSERT(false, "OpenGLError: %s", message);   }
    else
    {   CE_TRACE((char*)message)};
}

bool glInitialize(BumpAllocator* transientStorage)
{

    LoadGLFunctions();

    glDebugMessageCallback(&glDebugCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEBUG_OUTPUT);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    int fileSize = 0;
    char* vertShaderCode = File::ReadFile("./assets/shaders/quad.vert", &fileSize, transientStorage);
    char* fragShaderCode = File::ReadFile("./assets/shaders/quad.frag", &fileSize, transientStorage);

    if (!vertShaderCode || !fragShaderCode)
    {
        CE_ASSERT(false, "Failed to load Shaders");
        return false;
    }

    glShaderSource(vertexShader  , 1, &vertShaderCode, 0);
    glShaderSource(fragmentShader, 1, &fragShaderCode, 0);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    {
        int result;
        char shaderLog[512] = {};
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
        if(!result)
        {
            glGetShaderInfoLog(vertexShader, 512, 0, shaderLog);
            CE_ASSERT(false, "Failed to compile vertex shader");
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
        if(!result)
        {
            glGetShaderInfoLog(fragmentShader, 512, 0, shaderLog);
            CE_ASSERT(false, "Failed to compile fragment shader");
        }
    }

    glContext.program = glCreateProgram();
    glAttachShader(glContext.program, vertexShader);
    glAttachShader(glContext.program, fragmentShader);
    glLinkProgram(glContext.program);

    glDetachShader(glContext.program, vertexShader);
    glDetachShader(glContext.program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    {
        int width, height, channels;
        char* data = (char*)stbi_load(TEXTURE_PATH, &width, &height, &channels, 4);
        if (!data)
        {
            CE_ASSERT(false, "Failed to load texture atlas");
            return false;
        }

        glGenTextures(1, &glContext.texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, glContext.texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);

    glUseProgram(glContext.program);

    CE_TRACE("Initialized OpenGL Shaders");

    return true;
}

void glRender()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, input.screensizeX, input.screensizeY);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}