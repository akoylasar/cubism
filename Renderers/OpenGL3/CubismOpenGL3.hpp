// This is a modified version of imgui_impl_opengl3.h found under https://github.com/ocornut/imgui/tree/master/examples
/* 
The MIT License (MIT)

Copyright (c) 2014-2020 Omar Cornut

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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

