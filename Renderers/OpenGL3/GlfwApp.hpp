// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

#pragma once

#include <string>

struct GLFWwindow;

namespace Cubism
{
  class GlfwApp
  {
  public:
    GlfwApp(const std::string& title, int width, int height, int major, int minor);
    virtual ~GlfwApp();

    void setSwapInterval(int swapInterval);
    void setStickyKeys(bool state);
    void swapBuffers();
    void redraw();
    void run();
    void maximize();

    static void glfwErrorCallback(int error, const char* description);

  private:
    GlfwApp(const GlfwApp&) = delete;
    GlfwApp& operator=(const GlfwApp&) = delete;

  protected:
    // Window callbacks.
    virtual void onFramebufferSize(int width, int height, int windowWidth, int windowHeight) = 0;

    // Input callbacks.
    virtual void onCursorPos(float xPos, float yPos) = 0;
    virtual void onMouseButton(int button, int action, int mods) = 0;
    virtual void onScroll(float xOffset, float yOffset) = 0;

    virtual void onKey(int key, int scanCode, int action, int mods) = 0;

    virtual void setup(int width, int height, int windowWidth, int windowHeight) = 0;
    
    // @param deltaTime Time passed since last call in seconds.
    virtual void draw(float deltaTime) = 0;
    virtual void shutDown() = 0;

  private:
    void setupCallbacks();

  protected:
    GLFWwindow* mWindow;
    bool mDrawRequested;
  };
}
