#pragma once

#include <GL/glcorearb.h>

#include "Engine.h"
#include "Platform.h"
#include "PlatformWin32.h"

//TODO: Change OpenGL funtion wrappers from glFuncName to Renderer::FuncName
//TODO: Move OpenGl to RendererGl.h
//TODO: Multiple API support (Vulkan/DirectX?)

namespace Renderer
{}

static PFNGLCREATEPROGRAMPROC glCreateProgram_ptr;
static PFNGLDELETETEXTURESPROC glDeleteTextures_ptr;
static PFNGLGENTEXTURESPROC glGenTextures_ptr;
static PFNGLBINDTEXTUREPROC glBindTexture_ptr;
static PFNGLDRAWBUFFERPROC glDrawBuffer_ptr;
static PFNGLDRAWARRAYSPROC glDrawArrays_ptr;
static PFNGLCREATESHADERPROC glCreateShader_ptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_ptr;
static PFNGLUNIFORM1FPROC glUniform1f_ptr;
static PFNGLUNIFORM2FVPROC glUniform2fv_ptr;
static PFNGLUNIFORM3FVPROC glUniform3fv_ptr;
static PFNGLUNIFORM1IPROC glUniform1i_ptr;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv_ptr;
static PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor_ptr;
static PFNGLACTIVETEXTUREPROC glActiveTexture_ptr;
static PFNGLBUFFERSUBDATAPROC glBufferSubData_ptr;
static PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced_ptr;
static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer_ptr;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus_ptr;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers_ptr;
static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D_ptr;
static PFNGLDRAWBUFFERSPROC glDrawBuffers_ptr;
static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers_ptr;
static PFNGLBLENDFUNCIPROC glBlendFunci_ptr;
static PFNGLBLENDEQUATIONPROC glBlendEquation_ptr;
static PFNGLCLEARBUFFERFVPROC glClearBufferfv_ptr;
static PFNGLSHADERSOURCEPROC glShaderSource_ptr;
static PFNGLCOMPILESHADERPROC glCompileShader_ptr;
static PFNGLGETSHADERIVPROC glGetShaderiv_ptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_ptr;
static PFNGLATTACHSHADERPROC glAttachShader_ptr;
static PFNGLLINKPROGRAMPROC glLinkProgram_ptr;
static PFNGLVALIDATEPROGRAMPROC glValidateProgram_ptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv_ptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_ptr;
static PFNGLGENBUFFERSPROC glGenBuffers_ptr;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_ptr;
static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation_ptr;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_ptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_ptr;
static PFNGLBINDBUFFERPROC glBindBuffer_ptr;
static PFNGLBINDBUFFERBASEPROC glBindBufferBase_ptr;
static PFNGLBUFFERDATAPROC glBufferData_ptr;
static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv_ptr;
static PFNGLUSEPROGRAMPROC glUseProgram_ptr;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays_ptr;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers_ptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram_ptr;
static PFNGLDETACHSHADERPROC glDetachShader_ptr;
static PFNGLDELETESHADERPROC glDeleteShader_ptr;
static PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced_ptr;
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap_ptr;
static PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback_ptr;

/* 
static PFNGLTEXIMAGE2DPROC glTexImage2D_ptr;
static PFNGLTEXPARAMETERIPROC glTexParameteri_ptr;
static PFNGLTEXPARAMETERFVPROC glTexParameterfv_ptr;
static PFNGLCLEARPROC glClear_ptr;
static PFNGLCLEARCOLORPROC glClearColor_ptr;
static PFNGLREADBUFFERPROC glReadBuffer_ptr;
static PFNGLDEPTHMASKPROC glDepthMask_ptr;
static PFNGLDISABLEPROC glDisable_ptr;
static PFNGLENABLEPROC glEnable_ptr;
static PFNGLSCISSORPROC glScissor_ptr;
static PFNGLVIEWPORTPROC glViewport_ptr;
static PFNGLDEPTHFUNCPROC glDepthFunc_ptr;
static PFNGLCULLFACEPROC glCullFace_ptr;
static PFNGLBLENDFUNCPROC glBlendFunc_ptr;
static PFNGLFRONTFACEPROC glFrontFace_ptr; 
*/
 
 
void LoadGLFunctions()
{
    // Load OpenGL Functions from the Operating System / Graphics Card
    glCreateProgram_ptr           = (PFNGLCREATEPROGRAMPROC)          Platform::LoadGLFunction("glCreateProgram");
    glDeleteTextures_ptr          = (PFNGLDELETETEXTURESPROC)         Platform::LoadGLFunction("glDeleteTextures");
    glGenTextures_ptr             = (PFNGLGENTEXTURESPROC)            Platform::LoadGLFunction("glGenTextures");
    glBindTexture_ptr             = (PFNGLBINDTEXTUREPROC)            Platform::LoadGLFunction("glBindTexture");
    glDrawArrays_ptr              = (PFNGLDRAWARRAYSPROC)             Platform::LoadGLFunction("glDrawArrays");
    glCreateShader_ptr            = (PFNGLCREATESHADERPROC)           Platform::LoadGLFunction("glCreateShader");
    glGetUniformLocation_ptr      = (PFNGLGETUNIFORMLOCATIONPROC)     Platform::LoadGLFunction("glGetUniformLocation");
    glUniform1f_ptr               = (PFNGLUNIFORM1FPROC)              Platform::LoadGLFunction("glUniform1f");
    glUniform2fv_ptr              = (PFNGLUNIFORM2FVPROC)     Platform::LoadGLFunction("glUniform2fv");
    glUniform3fv_ptr              = (PFNGLUNIFORM3FVPROC) Platform::LoadGLFunction("glUniform3fv");
    glUniform1i_ptr               = (PFNGLUNIFORM1IPROC) Platform::LoadGLFunction("glUniform1i");
    glUniformMatrix4fv_ptr        = (PFNGLUNIFORMMATRIX4FVPROC) Platform::LoadGLFunction("glUniformMatrix4fv");
    glVertexAttribDivisor_ptr     = (PFNGLVERTEXATTRIBDIVISORPROC) Platform::LoadGLFunction("glVertexAttribDivisor");
    glActiveTexture_ptr           = (PFNGLACTIVETEXTUREPROC) Platform::LoadGLFunction("glActiveTexture");
    glBufferSubData_ptr           = (PFNGLBUFFERSUBDATAPROC) Platform::LoadGLFunction("glBufferSubData");
    glDrawArraysInstanced_ptr     = (PFNGLDRAWARRAYSINSTANCEDPROC) Platform::LoadGLFunction("glDrawArraysInstanced");
    glBindFramebuffer_ptr         = (PFNGLBINDFRAMEBUFFERPROC) Platform::LoadGLFunction("glBindFramebuffer");
    glCheckFramebufferStatus_ptr  = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) Platform::LoadGLFunction("glCheckFramebufferStatus");
    glGenFramebuffers_ptr         = (PFNGLGENFRAMEBUFFERSPROC) Platform::LoadGLFunction("glGenFramebuffers");
    glFramebufferTexture2D_ptr    = (PFNGLFRAMEBUFFERTEXTURE2DPROC) Platform::LoadGLFunction("glFramebufferTexture2D");
    glDrawBuffers_ptr             = (PFNGLDRAWBUFFERSPROC) Platform::LoadGLFunction("glDrawBuffers");
    glDeleteFramebuffers_ptr      = (PFNGLDELETEFRAMEBUFFERSPROC) Platform::LoadGLFunction("glDeleteFramebuffers");
    glBlendFunci_ptr              = (PFNGLBLENDFUNCIPROC) Platform::LoadGLFunction("glBlendFunci");
    glBlendEquation_ptr           = (PFNGLBLENDEQUATIONPROC) Platform::LoadGLFunction("glBlendEquation");
    glClearBufferfv_ptr           = (PFNGLCLEARBUFFERFVPROC) Platform::LoadGLFunction("glClearBufferfv");
    glShaderSource_ptr            = (PFNGLSHADERSOURCEPROC) Platform::LoadGLFunction("glShaderSource");
    glCompileShader_ptr           = (PFNGLCOMPILESHADERPROC) Platform::LoadGLFunction("glCompileShader");
    glGetShaderiv_ptr             = (PFNGLGETSHADERIVPROC) Platform::LoadGLFunction("glGetShaderiv");
    glGetShaderInfoLog_ptr        = (PFNGLGETSHADERINFOLOGPROC) Platform::LoadGLFunction("glGetShaderInfoLog");
    glAttachShader_ptr            = (PFNGLATTACHSHADERPROC) Platform::LoadGLFunction("glAttachShader");
    glLinkProgram_ptr             = (PFNGLLINKPROGRAMPROC) Platform::LoadGLFunction("glLinkProgram");
    glValidateProgram_ptr         = (PFNGLVALIDATEPROGRAMPROC) Platform::LoadGLFunction("glValidateProgram");
    glGetProgramiv_ptr            = (PFNGLGETPROGRAMIVPROC) Platform::LoadGLFunction("glGetProgramiv");
    glGetProgramInfoLog_ptr       = (PFNGLGETPROGRAMINFOLOGPROC) Platform::LoadGLFunction("glGetProgramInfoLog");
    glGenBuffers_ptr              = (PFNGLGENBUFFERSPROC) Platform::LoadGLFunction("glGenBuffers");
    glGenVertexArrays_ptr         = (PFNGLGENVERTEXARRAYSPROC) Platform::LoadGLFunction("glGenVertexArrays");
    glGetAttribLocation_ptr       = (PFNGLGETATTRIBLOCATIONPROC) Platform::LoadGLFunction("glGetAttribLocation");
    glBindVertexArray_ptr         = (PFNGLBINDVERTEXARRAYPROC) Platform::LoadGLFunction("glBindVertexArray");
    glEnableVertexAttribArray_ptr = (PFNGLENABLEVERTEXATTRIBARRAYPROC) Platform::LoadGLFunction("glEnableVertexAttribArray");
    glVertexAttribPointer_ptr     = (PFNGLVERTEXATTRIBPOINTERPROC) Platform::LoadGLFunction("glVertexAttribPointer");
    glBindBuffer_ptr              = (PFNGLBINDBUFFERPROC) Platform::LoadGLFunction("glBindBuffer");
    glBindBufferBase_ptr          = (PFNGLBINDBUFFERBASEPROC) Platform::LoadGLFunction("glBindBufferBase");
    glBufferData_ptr              = (PFNGLBUFFERDATAPROC) Platform::LoadGLFunction("glBufferData");
    glGetVertexAttribPointerv_ptr = (PFNGLGETVERTEXATTRIBPOINTERVPROC) Platform::LoadGLFunction("glGetVertexAttribPointerv");
    glUseProgram_ptr              = (PFNGLUSEPROGRAMPROC) Platform::LoadGLFunction("glUseProgram");
    glDeleteVertexArrays_ptr      = (PFNGLDELETEVERTEXARRAYSPROC) Platform::LoadGLFunction("glDeleteVertexArrays");
    glDeleteBuffers_ptr           = (PFNGLDELETEBUFFERSPROC) Platform::LoadGLFunction("glDeleteBuffers");
    glDeleteProgram_ptr           = (PFNGLDELETEPROGRAMPROC) Platform::LoadGLFunction("glDeleteProgram");
    glDetachShader_ptr            = (PFNGLDETACHSHADERPROC) Platform::LoadGLFunction("glDetachShader");
    glDeleteShader_ptr            = (PFNGLDELETESHADERPROC) Platform::LoadGLFunction("glDeleteShader");
    glDrawElementsInstanced_ptr   = (PFNGLDRAWELEMENTSINSTANCEDPROC) Platform::LoadGLFunction("glDrawElementsInstanced");
    glGenerateMipmap_ptr          = (PFNGLGENERATEMIPMAPPROC) Platform::LoadGLFunction("glGenerateMipmap");
    glDebugMessageCallback_ptr    = (PFNGLDEBUGMESSAGECALLBACKPROC)Platform::LoadGLFunction("glDebugMessageCallback");

/* 
    glTexImage2D_ptr = (PFNGLTEXIMAGE2DPROC)Platform::LoadGLFunction("glTexImage2D");
    glTexParameteri_ptr = (PFNGLTEXPARAMETERIPROC)Platform::LoadGLFunction("glTexParameteri");
    glTexParameterfv_ptr = (PFNGLTEXPARAMETERFVPROC)Platform::LoadGLFunction("glTexParameterfv");
    glClear_ptr = (PFNGLCLEARPROC)Platform::LoadGLFunction("glClear");
    glClearColor_ptr = (PFNGLCLEARCOLORPROC)Platform::LoadGLFunction("glClearColor");
    glReadBuffer_ptr = (PFNGLREADBUFFERPROC)Platform::LoadGLFunction("glReadBuffer");
    glDepthMask_ptr = (PFNGLDEPTHMASKPROC)Platform::LoadGLFunction("glDepthMask");
    glDisable_ptr = (PFNGLDISABLEPROC)Platform::LoadGLFunction("glDisable");
    glEnable_ptr = (PFNGLENABLEPROC)Platform::LoadGLFunction("glEnable");
    glScissor_ptr = (PFNGLSCISSORPROC)Platform::LoadGLFunction("glScissor");
    glViewport_ptr = (PFNGLVIEWPORTPROC)Platform::LoadGLFunction("glViewport");
    glDepthFunc_ptr = (PFNGLDEPTHFUNCPROC)Platform::LoadGLFunction("glDepthFunc");
    glCullFace_ptr = (PFNGLCULLFACEPROC)Platform::LoadGLFunction("glCullFace");
    glBlendFunc_ptr = (PFNGLBLENDFUNCPROC)Platform::LoadGLFunction("glBlendFunc");
    glFrontFace_ptr = (PFNGLFRONTFACEPROC)Platform::LoadGLFunction("glFrontFace");
*/
}
 

GLAPI GLuint APIENTRY glCreateProgram (void)
{
  return glCreateProgram_ptr();
}
 
GLAPI void APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures)
{
  glDeleteTextures_ptr(n, textures);
}
 
GLAPI void APIENTRY glGenTextures (GLsizei n, GLuint *textures)
{
  glGenTextures_ptr(n, textures);
}
 
GLAPI void APIENTRY glBindTexture (GLenum target, GLuint texture)
{
  glBindTexture_ptr(target, texture);
}
 
void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    glDrawArrays_ptr(mode, first, count);
}
 
GLuint glCreateShader(GLenum shaderType)
{
    return glCreateShader_ptr(shaderType);
}
 
GLint glGetUniformLocation(GLuint program, const GLchar* name)
{
    return glGetUniformLocation_ptr(program, name);
}
 
void glUniform1f(GLint location, GLfloat v0)
{
    glUniform1f_ptr(location, v0);
}
 
void glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
    glUniform2fv_ptr(location, count, value);
}
 
void glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
    glUniform3fv_ptr(location, count, value);
}
 
void glUniform1i(GLint location, GLint v0)
{
    glUniform1i_ptr(location, v0);
}
 
void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix4fv_ptr(location, count, transpose, value);
}
 
void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
    glVertexAttribDivisor_ptr(index, divisor);
}
 
void glActiveTexture(GLenum texture)
{
    glActiveTexture_ptr(texture);
}
 
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
    glBufferSubData_ptr(target, offset, size, data);
}
 
void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
{
    glDrawArraysInstanced_ptr(mode, first, count, instanceCount);
}
 
void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
    glBindFramebuffer_ptr(target, framebuffer);
}
 
GLenum glCheckFramebufferStatus(GLenum target)
{
    return glCheckFramebufferStatus_ptr(target);
}
 
void glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
    glGenFramebuffers_ptr(n, framebuffers);
}
 
void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    glFramebufferTexture2D_ptr(target, attachment, textarget, texture, level);
}
 
void glDrawBuffers(GLsizei n, const GLenum* bufs)
{
    glDrawBuffers_ptr(n, bufs);
}
 
void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
    glDeleteFramebuffers_ptr(n, framebuffers);
}
 
void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
    glBlendFunci_ptr(buf, src, dst);
}
 
void glBlendEquation(GLenum mode)
{
    glBlendEquation_ptr(mode);
}
 
void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
    glClearBufferfv_ptr(buffer, drawbuffer, value);
}
 
void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths)
{
    glShaderSource_ptr(shader, count, strings, lengths);
}
 
void glCompileShader(GLuint shader)
{
    glCompileShader_ptr(shader);
}
 
void glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
    glGetShaderiv_ptr(shader, pname, params);
}
 
void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
    glGetShaderInfoLog_ptr(shader, bufSize, length, infoLog);
}
 
void glAttachShader(GLuint program, GLuint shader)
{
    glAttachShader_ptr(program, shader);
}
 
void glLinkProgram(GLuint program)
{
    glLinkProgram_ptr(program);
}
 
void glValidateProgram(GLuint program)
{
    glValidateProgram_ptr(program);
}
 
void glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
    glGetProgramiv_ptr(program, pname, params);
}
 
void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
    glGetProgramInfoLog_ptr(program, bufSize, length, infoLog);
}
 
void glGenBuffers(GLsizei n, GLuint* buffers)
{
    glGenBuffers_ptr(n, buffers);
}
 
void glGenVertexArrays(GLsizei n, GLuint* arrays)
{
    glGenVertexArrays_ptr(n, arrays);
}
 
GLint glGetAttribLocation(GLuint program, const GLchar* name)
{
    return glGetAttribLocation_ptr(program, name);
}
 
void glBindVertexArray(GLuint array)
{
    glBindVertexArray_ptr(array);
}
 
void glEnableVertexAttribArray(GLuint index)
{
    glEnableVertexAttribArray_ptr(index);
}
 
void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
    glVertexAttribPointer_ptr(index, size, type, normalized, stride, pointer);
}
 
void glBindBuffer(GLenum target, GLuint buffer)
{
    glBindBuffer_ptr(target, buffer);
}
 
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
    glBindBufferBase_ptr(target, index, buffer);
}
 
void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
    glBufferData_ptr(target, size, data, usage);
}
 
void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
    glGetVertexAttribPointerv_ptr(index, pname, pointer);
}
 
void glUseProgram(GLuint program)
{
    glUseProgram_ptr(program);
}
 
void glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
    glDeleteVertexArrays_ptr(n, arrays);
}
 
void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
    glDeleteBuffers_ptr(n, buffers);
}
 
void glDeleteProgram(GLuint program)
{
    glDeleteProgram_ptr(program);
}
 
void glDetachShader (GLuint program, GLuint shader)
{
    glDetachShader_ptr(program, shader);
}
 
void glDeleteShader(GLuint shader)
{
    glDeleteShader_ptr(shader);
}
 
void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount)
{
    glDrawElementsInstanced_ptr(mode, count, type, indices, instancecount);
}
 
void glGenerateMipmap(GLenum target)
{
    glGenerateMipmap_ptr(target);
}
 
void glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam)
{
  glDebugMessageCallback_ptr(callback, userParam);
}

/* 
GLAPI void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width,
                                  GLsizei height, GLint border, GLenum format, GLenum type,
                                  const void *pixels)
{
  glTexImage2D_ptr(target, level, internalformat, width, height,
                   border, format, type, pixels);
}
 
GLAPI void APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param)
{
  glTexParameteri_ptr(target, pname, param);
}
 
GLAPI void APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
  glTexParameterfv_ptr(target, pname, params);
}
 
GLAPI void APIENTRY glClear (GLbitfield mask)
{
  glClear_ptr(mask);
}
 
GLAPI void APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  glClearColor_ptr(red, green, blue, alpha);
}
 
void glReadBuffer(GLenum mode)
{
    glReadBuffer_ptr(mode);
}
 
void glDepthMask(GLboolean flag)
{
    glDepthMask_ptr(flag);
}
 
void glDisable(GLenum cap)
{
    glDisable_ptr(cap);
}
 

void glEnable(GLenum cap)
{
    glEnable_ptr(cap);
} 

 
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glScissor_ptr(x, y, width, height);
}
 
void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport_ptr(x, y, width, height);
}
 
void glDepthFunc(GLenum func)
{
    glDepthFunc_ptr(func);
}
 
void glCullFace(GLenum mode)
{
    glCullFace_ptr(mode);
}
 
void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    glBlendFunc_ptr(sfactor, dfactor);
}
 
void glFrontFace(GLenum mode)
{
    glFrontFace_ptr(mode);
} 
*/