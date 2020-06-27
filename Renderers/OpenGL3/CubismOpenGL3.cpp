// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

#include "CubismOpenGL3.hpp"

#include <string>
#include <iostream>

// Auto-enable GLES on matching platforms
#if !defined(CUBISM_RENDERER_OPENGL_ES2) && !defined(CUBISM_RENDERER_OPENGL_ES3)
#if (defined(__APPLE__) && (TARGET_OS_IOS || TARGET_OS_TV)) || (defined(__ANDROID__))
#define CUBISM_RENDERER_OPENGL_ES3 // iOS, Android -> GL ES 3, "#version 300 es"
#elif defined(__EMSCRIPTEN__)
#define CUBISM_RENDERER_OPENGL_ES2 // Emscripten -> GL ES 2, "#version 100"
#endif
#endif

#define CUBISM_OFFSETOF(type, member) offsetof(type, member)

#if defined(CUBISM_RENDERER_OPENGL_ES2) || defined(CUBISM_RENDERER_OPENGL_ES3)
#undef CUBISM_RENDERER_OPENGL_LOADER_GL3W
#undef CUBISM_RENDERER_OPENGL_LOADER_GLEW
#undef CUBISM_RENDERER_OPENGL_LOADER_GLAD
#undef CUBISM_RENDERER_OPENGL_LOADER_GLBINDING2
#undef CUBISM_RENDERER_OPENGL_LOADER_GLBINDING3
#undef CUBISM_RENDERER_OPENGL_LOADER_CUSTOM
#endif

// GL includes
#if defined(CUBISM_RENDERER_OPENGL_ES2)
#include <GLES2/gl2.h>
#elif defined(CUBISM_RENDERER_OPENGL_ES3)
#if (defined(__APPLE__) && (TARGET_OS_IOS || TARGET_OS_TV))
#include <OpenGLES/ES3/gl.h> // Use GL ES 3
#else
#include <GLES3/gl3.h> // Use GL ES 3
#endif
#else
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(CUBISM_RENDERER_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Needs to be initialized with gl3wInit() in user's code
#elif defined(CUBISM_RENDERER_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Needs to be initialized with glewInit() in user's code.
#elif defined(CUBISM_RENDERER_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Needs to be initialized with gladLoadGL() in user's code.
#elif defined(CUBISM_RENDERER_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Needs to be initialized with glbinding::Binding::initialize() in user's code.
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(CUBISM_RENDERER_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Needs to be initialized with glbinding::initialize() in user's code.
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include CUBISM_RENDERER_OPENGL_LOADER_CUSTOM
#endif
#endif

namespace
{
  // OpenGL Data
  static GLuint gGlVersion = 0; // Extracted at runtime using GL_MAJOR_VERSION, GL_MINOR_VERSION queries.
  static std::string gGlslVersionString = ""; // Specified by user or detected based on compile time GL settings.
  static GLuint gFontTexture = 0; GLuint gWhiteTexture = 0;
  static GLuint gShaderHandle = 0, gVertHandle = 0, gFragHandle = 0;
  static int gAttribLocationTex = 0; static int gAttribLocationTransformationMatrix = 0; // Uniforms location.
  static int gAttribLocationVertexPosition = 0, gAttribLocationVertexColor = 0, gAttribLocationVertexUv = 0;// Vertex attributes location.
  static unsigned int gVboHandle = 0, gElementsHandle = 0;
}

namespace Cubism
{
  namespace Renderer
  {
    namespace OpenGL
    {
      void createDeviceObjects();
      void destroyDeviceObjects();
      void createTextures();
      void createTexture(GLuint texture, GLsizei width, GLsizei height, const unsigned char* const data);
      
      bool init(const char* version)
      {
        std::string glslVersion(version);
#if !defined(CUBISM_RENDERER_OPENGL_ES2)
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        gGlVersion = major * 1000 + minor;
#else
        gGlVersion = 2000; // GLES 2
#endif
        
        // Store GLSL version string so we can refer to it later in case we recreate shaders.
        // Note: GLSL version is NOT the same as GL version. Leave this to NULL if unsure.
#if defined(CUBISM_RENDERER_OPENGL_ES2)
        if (glslVersion.empty())
          glslVersion = "#version 100";
#elif defined(CUBISM_RENDERER_OPENGL_ES3)
        if (glslVersion.empty())
          glslVersion = "#version 300 es";
#else
        if (glslVersion.empty())
          glslVersion = "#version 130";
#endif
        gGlslVersionString = glslVersion + "\n";
        
        // Make a dummy GL call (we don't actually need the result) to ensure everything OpenGL is all set up.
        GLint currentTexture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
        return true;
      }
      
      void shutdown()
      {
        destroyDeviceObjects();
      }
      
      void newFrame()
      {
        if (!gShaderHandle)
          createDeviceObjects();
      }
      
      static void setupRenderState(const Vec2& displayPos, const Vec2& displaySize, GLuint vao)
      {
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
#ifdef GL_POLYGON_MODE
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
        glUseProgram(gShaderHandle);
        glUniform1i(gAttribLocationTex, 0);
        
        CUBISM_UNUSED(vao);
#ifndef CUBISM_RENDERER_OPENGL_ES2
        glBindVertexArray(vao);
#endif
        
        // Bind vertex/index buffers and setup attributes for Cubism::DrawList.
        glBindBuffer(GL_ARRAY_BUFFER, gVboHandle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gElementsHandle);
        glEnableVertexAttribArray(gAttribLocationVertexPosition);
        glEnableVertexAttribArray(gAttribLocationVertexColor);
        glEnableVertexAttribArray(gAttribLocationVertexUv);
        glVertexAttribPointer(gAttribLocationVertexPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)CUBISM_OFFSETOF(Vertex, position));
        glVertexAttribPointer(gAttribLocationVertexColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)CUBISM_OFFSETOF(Vertex, color));
        glVertexAttribPointer(gAttribLocationVertexUv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)CUBISM_OFFSETOF(Vertex, uv));
      }
      
      void render()
      {
        // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
        const IO& io = Cubism::getIO();
        const Vec2 fbSize = io.displaySize * io.displayFramebufferScale;
        
        int fbWidth = (int)fbSize.x; int fbHeight = (int)fbSize.y;
        if (fbWidth <= 0 || fbHeight <= 0)
          return;
        
        DrawList* drawList = Cubism::getDrawList();
        
        // Backup GL state.
        GLenum lastActiveTexture; glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&lastActiveTexture);
        GLint lastTexture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
        
        GLint lastProgram; glGetIntegerv(GL_CURRENT_PROGRAM, &lastProgram);
#ifdef GL_SAMPLER_BINDING
        GLint lastSampler; glGetIntegerv(GL_SAMPLER_BINDING, &lastSampler);
#endif
        GLint lastArrayBuffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &lastArrayBuffer);
#ifndef CUBISM_RENDERER_OPENGL_ES2
        GLint lastVertexArrayObject; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &lastVertexArrayObject);
#endif
#ifdef GL_POLYGON_MODE
        GLint lastPolygonMode[2]; glGetIntegerv(GL_POLYGON_MODE, lastPolygonMode);
#endif
        GLint lastViewport[4]; glGetIntegerv(GL_VIEWPORT, lastViewport);
        GLenum lastBlendSrcRgb; glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&lastBlendSrcRgb);
        GLenum lastBlendDstRgb; glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&lastBlendDstRgb);
        GLenum lastBlendSrcAlpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&lastBlendSrcAlpha);
        GLenum lastBlendDstAlpha; glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&lastBlendDstAlpha);
        GLenum lastBlendEquationRgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&lastBlendEquationRgb);
        GLenum lastBlendEquationAlpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&lastBlendEquationAlpha);
        GLboolean lastEnableBlend = glIsEnabled(GL_BLEND);
        GLboolean lastEnableCullFace = glIsEnabled(GL_CULL_FACE);
        GLboolean lastEnableDepthTest = glIsEnabled(GL_DEPTH_TEST);
        
        // Setup desired GL state
        // Recreate the VAO every time (this is to easily allow multiple GL contexts to be rendered to. VAO are not shared among GL contexts)
        // The renderer would actually work without any VAO bound, but then our VertexAttrib calls would overwrite the default one currently bound.
        GLuint vertexArrayObject = 0;
#ifndef CUBISM_RENDERER_OPENGL_ES2
        glGenVertexArrays(1, &vertexArrayObject);
#endif
        // Setup viewport which should amount to our framebuffer size.
        const Vec2 posInFbSpace = io.displayPosition * io.displayFramebufferScale;
        glViewport(posInFbSpace.x, posInFbSpace.y, (GLsizei)fbWidth, (GLsizei)fbHeight);
        
        setupRenderState(io.displayPosition, io.displaySize, vertexArrayObject);
        
        // Upload vertex/index buffers.
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)drawList->getVertices().size() * sizeof(Vertex), (const GLvoid*)drawList->getVertices().data(), GL_STREAM_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)drawList->getIndices().size() * sizeof(Index), (const GLvoid*)drawList->getIndices().data(), GL_STREAM_DRAW);
        
        glActiveTexture(GL_TEXTURE0);

        // Render.
        const DrawCommndsList& drawCmds = drawList->getDrawCommands();
        for (int i = 0; i < drawCmds.size(); ++i)
        {
          const DrawCommand& drawCmd = drawCmds[i];
          glBindTexture(GL_TEXTURE_2D, drawCmd.isText ? gFontTexture : gWhiteTexture);
          Mat4& matrix = drawList->getMatrix(drawCmd.matrixIndex);
          glUniformMatrix4fv(gAttribLocationTransformationMatrix, 1, GL_FALSE, matrix.data());
          
          glDrawElements(GL_TRIANGLES, (GLsizei)drawCmd.elementCount, GL_UNSIGNED_INT, (void*)(intptr_t)(drawCmd.indexOffset * sizeof(Index)));
        }
        
        // Destroy the temporary VAO.
#ifndef CUBISM_RENDERER_OPENGL_ES2
        glDeleteVertexArrays(1, &vertexArrayObject);
#endif
        
        // Restore modified GL state.
        glUseProgram(lastProgram);
        glBindTexture(GL_TEXTURE_2D, lastTexture);
        glActiveTexture(lastActiveTexture);
#ifndef CUBISM_RENDERER_OPENGL_ES2
        glBindVertexArray(lastVertexArrayObject);
#endif
        glBindBuffer(GL_ARRAY_BUFFER, lastArrayBuffer);
        glBlendEquationSeparate(lastBlendEquationRgb, lastBlendEquationAlpha);
        glBlendFuncSeparate(lastBlendSrcRgb, lastBlendDstRgb, lastBlendSrcAlpha, lastBlendDstAlpha);
        if (lastEnableBlend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
        if (lastEnableCullFace) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
        if (lastEnableDepthTest) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
#ifdef GL_POLYGON_MODE
        glPolygonMode(GL_FRONT_AND_BACK, (GLenum)lastPolygonMode[0]);
#endif
        glViewport(lastViewport[0], lastViewport[1], (GLsizei)lastViewport[2], (GLsizei)lastViewport[3]);
      }
      
      static bool CheckShader(GLuint handle, const char* desc)
      {
        GLint status = 0, logLength = 0;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
        if ((GLboolean)status == GL_FALSE)
          std::cerr << "[Cubism]: Failed to compile " << desc << "\n";
        
        if (logLength > 1)
        {
          std::vector<GLchar> buffer;
          buffer.resize((int)(logLength + 1));
          glGetShaderInfoLog(handle, logLength, nullptr, buffer.data());
          std::string errMsg(buffer.begin(), buffer.end());
          std::cerr << errMsg << "\n";
        }
        return (GLboolean)status == GL_TRUE;
      }
      
      static bool CheckProgram(GLuint handle, const char* desc)
      {
        GLint status = 0, logLength = 0;
        glGetProgramiv(handle, GL_LINK_STATUS, &status);
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLength);
        if ((GLboolean)status == GL_FALSE)
          std::cerr << "[Cubism]: Failed to link " << desc << " with GLSL " << gGlslVersionString << "\n";
        if (logLength > 1)
        {
          std::vector<char> buffer;
          buffer.resize((int)(logLength + 1));
          glGetProgramInfoLog(handle, logLength, nullptr, (GLchar*)buffer.data());
          std::cerr << buffer.data() << "\n";
        }
        return (GLboolean)status == GL_TRUE;
      }
      
      void createDeviceObjects()
      {
        // Backup GL state.
        GLint lastTexture, lastArrayBuffer;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &lastArrayBuffer);
#ifndef CUBISM_RENDERER_OPENGL_ES2
        GLint lastVertexArray;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &lastVertexArray);
#endif
        // Parse GLSL version string.
        int glslVersion = 130;
        sscanf(gGlslVersionString.c_str(), "#version %d", &glslVersion);
        
        const GLchar* vsGlsl120 =
        "uniform mat4 transformation;\n"
        "attribute vec3 position;\n"
        "attribute vec4 color;\n"
        "attribute vec2 uv;\n"
        "varying vec4 fragColor;\n"
        "varying vec2 fragUv;\n"
        "void main()\n"
        "{\n"
        "  fragColor = color;\n"
        "  fragUv = uv;\n"
        "  gl_Position = transformation * vec4(position.xyz, 1);\n"
        "}\n";
        
        const GLchar* vsGlsl130 =
        "uniform mat4 transformation;\n"
        "in vec3 position;\n"
        "in vec4 color;\n"
        "in vec2 uv;\n"
        "out vec4 fragColor;\n"
        "out vec2 fragUv;\n"
        "void main()\n"
        "{\n"
        "  fragColor = color;\n"
        "  fragUv = uv;\n"
        "  gl_Position = transformation * vec4(position.xyz, 1);\n"
        "}\n";
        
        const GLchar* vsGlsl300ES =
        "precision mediump float;\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec4 color;\n"
        "layout (location = 2) in vec2 uv;\n"
        "uniform mat4 transformation;\n"
        "out vec4 fragColor;\n"
        "out vec2 fragUv;\n"
        "void main()\n"
        "{\n"
        "  fragColor = color;\n"
        "  fragUv = uv;\n"
        "  gl_Position = transformation * vec4(position.xyz, 1);\n"
        "}\n";
        
        const GLchar* vsGlsl410Core =
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec4 color;\n"
        "layout (location = 2) in vec2 uv;\n"
        "uniform mat4 transformation;\n"
        "out vec4 fragColor;\n"
        "out vec2 fragUv;\n"
        "void main()\n"
        "{\n"
        "  fragColor = color;\n"
        "  fragUv = uv;\n"
        "  gl_Position = transformation * vec4(position.xyz, 1);\n"
        "}\n";
        
        const GLchar* fsGlsl120 =
        "#ifdef GL_ES\n"
        "  precision mediump float;\n"
        "#endif\n"
        "varying vec4 fragColor;\n"
        "varying vec2 fragUv;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "  gl_FragColor = texture2D(tex, fragUv.xy).r * fragColor;\n"
        "}\n";
        
        const GLchar* fsGlsl130 =
        "in vec4 fragColor;\n"
        "in vec2 fragUv;\n"
        "out vec4 outColor;\n"
        "uniform sampler2D tex;\n"
        "void main()\n"
        "{\n"
        "  outColor = texture(tex, fragUv.xy).r * fragColor;\n"
        "}\n";
        
        const GLchar* fsGlsl300ES =
        "precision mediump float;\n"
        "in vec4 fragColor;\n"
        "in vec2 fragUv;\n"
        "uniform sampler2D tex;\n"
        "layout (location = 0) out vec4 outColor;\n"
        "void main()\n"
        "{\n"
        "    outColor = texture(tex, fragUv.xy).r * fragColor;\n"
        "}\n";
        
        const GLchar* fsGlsl410Core =
        "in vec4 fragColor;\n"
        "in vec2 fragUv;\n"
        "uniform sampler2D tex;\n"
        "layout (location = 0) out vec4 outColor;\n"
        "void main()\n"
        "{\n"
        "    outColor = texture(tex, fragUv.xy).r * fragColor;\n"
        "}\n";
        
        // Select shaders matching our GLSL versions.
        const GLchar* vs = nullptr;
        const GLchar* fs = nullptr;
        if (glslVersion < 130)
        {
          vs = vsGlsl120;
          fs = fsGlsl120;
        }
        else if (glslVersion >= 410)
        {
          vs = vsGlsl410Core;
          fs = fsGlsl410Core;
        }
        else if (glslVersion == 300)
        {
          vs = vsGlsl300ES;
          fs = fsGlsl300ES;
        }
        else
        {
          vs = vsGlsl130;
          fs = fsGlsl130;
        }
        
        // Create shaders.
        const GLchar* vsWithVersion[2] = {gGlslVersionString.c_str(), vs};
        gVertHandle = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(gVertHandle, 2, vsWithVersion, nullptr);
        glCompileShader(gVertHandle);
        CheckShader(gVertHandle, "vertex shader");
        
        const GLchar* fsWithVersion[2] = {gGlslVersionString.c_str(), fs};
        gFragHandle = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(gFragHandle, 2, fsWithVersion, nullptr);
        glCompileShader(gFragHandle);
        CheckShader(gFragHandle, "fragment shader");
        
        gShaderHandle = glCreateProgram();
        glAttachShader(gShaderHandle, gVertHandle);
        glAttachShader(gShaderHandle, gFragHandle);
        glLinkProgram(gShaderHandle);
        CheckProgram(gShaderHandle, "shader program");
        
        gAttribLocationTex = glGetUniformLocation(gShaderHandle, "tex");
        gAttribLocationTransformationMatrix = glGetUniformLocation(gShaderHandle, "transformation");
        gAttribLocationVertexPosition = glGetAttribLocation(gShaderHandle, "position");
        gAttribLocationVertexColor = glGetAttribLocation(gShaderHandle, "color");
        gAttribLocationVertexUv = glGetAttribLocation(gShaderHandle, "uv");
        
        // Create buffers.
        glGenBuffers(1, &gVboHandle);
        glGenBuffers(1, &gElementsHandle);
        
        createTextures();
        
        // Restore modified GL state.
        glBindTexture(GL_TEXTURE_2D, lastTexture);
        glBindBuffer(GL_ARRAY_BUFFER, lastArrayBuffer);
#ifndef CUBISM_RENDERER_OPENGL_ES2
        glBindVertexArray(lastArrayBuffer);
#endif
      }
      
      void createTextures()
      {
        GLint lastTexture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
        
        // Font texture.
        const FontData& fontData = Cubism::getFontData();
        glGenTextures(1, &gFontTexture);
        createTexture(gFontTexture, fontData.resolution, fontData.resolution, fontData.textureData.data());

        // White 1x1 texture.
        glGenTextures(1, &gWhiteTexture);
        const unsigned char whitePixel = 0xff;
        createTexture(gWhiteTexture, 1, 1, &whitePixel);
        
        // Restore state.
        glBindTexture(GL_TEXTURE_2D, lastTexture);
      }
      
      void createTexture(GLuint texture, GLsizei width, GLsizei height, const unsigned char* const data)
      {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifdef GL_UNPACK_ROW_LENGTH
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
      }
      
      void destroyDeviceObjects()
      {
        if (gVboHandle) { glDeleteBuffers(1, &gVboHandle); gVboHandle = 0; }
        if (gElementsHandle) { glDeleteBuffers(1, &gElementsHandle); gElementsHandle = 0; }
        if (gShaderHandle && gVertHandle) { glDetachShader(gShaderHandle, gVertHandle); }
        if (gShaderHandle && gFragHandle) { glDetachShader(gShaderHandle, gFragHandle); }
        if (gVertHandle) { glDeleteShader(gVertHandle); gVertHandle = 0; }
        if (gFragHandle) { glDeleteShader(gFragHandle); gFragHandle = 0; }
        if (gShaderHandle) { glDeleteProgram(gShaderHandle); gShaderHandle = 0; }
        if (gFontTexture) glDeleteTextures(1, &gFontTexture);
      }
    }
  }
}
