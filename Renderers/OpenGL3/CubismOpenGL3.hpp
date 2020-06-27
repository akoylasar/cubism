// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

#pragma once

#include "Cubism.hpp"

namespace Cubism
{
  namespace Renderer
  {
    namespace OpenGL
    {
      bool init(const char* glslVersion);
      void shutdown();
      void newFrame();
      void render();
    }
  }
}

// Specific OpenGL versions
// #define CUBISM_RENDERER_OPENGL_ES2 // Auto-detected on Emscripten
// #define CUBISM_RENDERER_OPENGL_ES3 // Auto-detected on iOS/Android

// Desktop OpenGL: attempt to detect default GL loader based on available header files.
// If auto-detection fails or doesn't select the same GL loader file as used by your application,
// you are likely to get a crash in Cubism::Renderer::OpenGL::Init().
#if !defined(CUBISM_RENDERER_OPENGL_LOADER_GL3W) \
 && !defined(CUBISM_RENDERER_OPENGL_LOADER_GLEW) \
 && !defined(CUBISM_RENDERER_OPENGL_LOADER_GLAD) \
 && !defined(CUBISM_RENDERER_OPENGL_LOADER_GLBINDING2) \
 && !defined(CUBISM_RENDERER_OPENGL_LOADER_GLBINDING3) \
 && !defined(CUBISM_RENDERER_OPENGL_LOADER_CUSTOM)
  #if defined(__has_include)
    #if __has_include(<GL/glew.h>)
      #define CUBISM_RENDERER_OPENGL_LOADER_GLEW
    #elif __has_include(<glad/glad.h>)
      #define CUBISM_RENDERER_OPENGL_LOADER_GLAD
    #elif __has_include(<GL/gl3w.h>)
      #define CUBISM_RENDERER_OPENGL_LOADER_GL3W
    #elif __has_include(<glbinding/glbinding.h>)
      #define CUBISM_RENDERER_OPENGL_LOADER_GLBINDING3
    #elif __has_include(<glbinding/Binding.h>)
      #define CUBISM_RENDERER_OPENGL_LOADER_GLBINDING2
    #else
      #error "Cannot detect OpenGL loader!"
    #endif
  #else
    #define CUBISM_RENDERER_OPENGL_LOADER_GL3W
  #endif
#endif

