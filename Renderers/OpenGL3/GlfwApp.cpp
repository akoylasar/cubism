// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

#include "GlfwApp.hpp"

#include "Cubism.hpp"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <exception>

namespace Cubism
{
  GlfwApp::GlfwApp(const std::string& title, int width, int height, int major, int minor)
    : mWindow(nullptr),
      mDrawRequested(true)
  {
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
      throw std::runtime_error("GlfwApp: Failed to initialise glfw.\n");
    }

    // Set window hints valid throughout the lifetime of the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!mWindow)
    {
      glfwTerminate();
      CUBISM_ASSERT_MSG(false, "GlfwApp: Failed to create an OpenGL");
    }

    glfwSetWindowUserPointer(mWindow, this);
    setupCallbacks();

    glfwMakeContextCurrent(mWindow);

    if (gl3wInit())
    {
      glfwDestroyWindow(mWindow);
      glfwTerminate();

      throw std::runtime_error("GlfwApp: Failed to initialize gl3w..\n");
    }
  }

  GlfwApp::~GlfwApp()
  {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
  }

  void GlfwApp::glfwErrorCallback(int error, const char* description)
  {
    std::cerr << "Error code: " << error << ". Error description: " << description << "\n";
  }

  void GlfwApp::setSwapInterval(int swapInterval)
  {
    glfwSwapInterval(swapInterval);
  }

  void GlfwApp::setStickyKeys(bool state)
  {
    glfwSetInputMode(mWindow, GLFW_LOCK_KEY_MODS, state);
  }

  void GlfwApp::swapBuffers()
  {
    glfwSwapBuffers(mWindow);
  }

  void GlfwApp::redraw()
  {
    mDrawRequested = true;
  }

  void GlfwApp::run()
  {
    int w, h; glfwGetWindowSize(mWindow, &w, &h);
    int fbW, fbH; glfwGetFramebufferSize(mWindow, &fbW, &fbH);
    setup(fbW, fbH, w, h);
    
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(mWindow))
    {
      double currentTime = glfwGetTime();
      const double deltaTime = currentTime - lastTime;
      
      if (mDrawRequested)
      {
        mDrawRequested = false;
        draw(static_cast<float>(deltaTime));
      }
      
      glfwPollEvents();

      lastTime = currentTime;
    }

    shutDown();
  }

  void GlfwApp::maximize()
  {
    glfwMaximizeWindow(mWindow);
  }

  void GlfwApp::setupCallbacks()
  {
    glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
    {
      int w, h; glfwGetWindowSize(window, &w, &h);
      GlfwApp* app = static_cast<GlfwApp*>(glfwGetWindowUserPointer(window));
      app->onFramebufferSize(width, height, w, h);
    });

    glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
    {
      GlfwApp* app = static_cast<GlfwApp*>(glfwGetWindowUserPointer(window));
      app->onCursorPos(static_cast<float>(xPos), static_cast<float>(yPos));
    });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
    {
      GlfwApp* app = static_cast<GlfwApp*>(glfwGetWindowUserPointer(window));
      app->onMouseButton(button, action, mods);
    });

    glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
    {
      GlfwApp* app = static_cast<GlfwApp*>(glfwGetWindowUserPointer(window));
      app->onScroll(static_cast<float>(xOffset), static_cast<float>(yOffset));
    });

    glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
    {
      GlfwApp* app = static_cast<GlfwApp*>(glfwGetWindowUserPointer(window));
      app->onKey(key, scanCode, action, mods);
    });
  }
}
