// Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

#include <vector>
#include <iostream>
#include <memory>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Cubism.hpp"
#include "CubismOpenGL3.hpp"

#include "GlfwApp.hpp"

namespace
{
  constexpr int kWindowWidth = 512;
  constexpr int kWindowHeight = 512;
  constexpr int kGlMajor = 4;
  constexpr int kGlMinor = 1;
  const char* kGlslVersion = "#version 410";
  
  inline bool checkError()
  {
    GLenum err;
    if((err = glGetError()) != GL_NO_ERROR)
    {
      std::cout << "GL error: 0x0" << std::hex << err << " occured.\n";
      return true;
    }
    return false;
  }
}

class MainApp : public Cubism::GlfwApp
{
public:
  MainApp(const std::string& title, int width, int height, int major, int minor)
  : GlfwApp::GlfwApp(title, width, height, major, minor),
    mMiddleMousePressed(false),
    mLastX(0.0),
    mLastY(0.0),
    mShiftPressed(false),
    mWidth(kWindowWidth),
    mHeight(kWindowHeight)
  {
  }
  
protected:
  void onFramebufferSize(int width, int height, int windowWidth, int windowHeight) override
  {
    glViewport(0, 0, width, height);
    Cubism::IO& io = Cubism::getIO();
    updateIO(io, width, height, windowWidth, windowHeight);
  }
  
  void onCursorPos(float xPos, float yPos) override
  {
    mLastX = xPos;
    mLastY = yPos;
  }
  
  void onMouseButton(int button, int action, int mods) override
  {
    const bool middle = (button == GLFW_MOUSE_BUTTON_MIDDLE);
    const bool pressed = (action == (int)GLFW_PRESS);
    mMiddleMousePressed = middle && pressed;
  }
  
  void onScroll(float xOffset, float yOffset) override
  {
  }
  
  void onKey(int key, int scanCode, int action, int mods) override
  {
    const bool leftShift = (key == GLFW_KEY_LEFT_SHIFT);
    const bool pressed = (action == (int)GLFW_PRESS);
    const bool repeated = (action == (int)GLFW_REPEAT);
    mShiftPressed = leftShift && (pressed || repeated);
  }
  
  void setup(int width, int height, int windowWidth, int windowHeight) override
  {
    setSwapInterval(1);
    Cubism::IO io;
    updateIO(io, width, height, windowWidth, windowHeight);
    Cubism::createContext(io);
    Cubism::Renderer::OpenGL::init(kGlslVersion);
  }
  
  void draw(float deltaTime) override
  {
    Cubism::IO& io = Cubism::getIO();
    io.deltaTime = static_cast<float>(deltaTime * 1000.0f); // (ms)
    
    checkError();
    
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Cubism::newFrame();
    Cubism::Renderer::OpenGL::newFrame();

    Cubism::DrawList* drawList = Cubism::getDrawList();
    addPrimitives(*drawList);
    
    Cubism::render();
    Cubism::Renderer::OpenGL::render();
    checkError();

    swapBuffers();
    redraw();
  }
  
  void shutDown() override
  {
  }
  
private:
  void addPrimitives(Cubism::DrawList& drawList)
  {
    // Setup orthographic projection matrix.
    Cubism::IO io = Cubism::getIO();
    const float L = io.displayPosition.x;
    const float R = L + io.displaySize.x;
    const float B = io.displayPosition.y;
    const float T = B + io.displaySize.y;
    const Cubism::Mat4 orthoMat =
    {
      { 2.0f/(R-L),   0.0f,         0.0f,   0.0f },
      { 0.0f,         2.0f/(T-B),   0.0f,   0.0f },
      { 0.0f,         0.0f,        -1.0f,   0.0f },
      { (R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f },
    };
    
    drawList.pushMatrix(orthoMat);

    using Cubism::kWhite; using Cubism::kRed; using Cubism::kGreen; using Cubism::kBlue;
    
    const Cubism::Vec2 invertedMouse {mLastX, mHeight - mLastY};
    drawList.addLine(Cubism::Vec2(0, mHeight), invertedMouse, kBlue, 10);

    const Cubism::Vec2 quadPosition {100, 100};

    drawList.addQuad(quadPosition, 200, kWhite, 2);

    const Cubism::Vec2 circlePosition {mWidth / 2, mHeight / 2};
    drawList.addCircle(circlePosition, 50, kWhite, 30, 4);

    const Cubism::Vec2 filledQuadPosition {mWidth / 3, 0};
    drawList.addQuadFilled(filledQuadPosition, 50, Cubism::toColor(255, 255, 255, 127));

    const Cubism::Vec2 filledPentagonPosition {mWidth / 2 + 100, mHeight / 2 + 100};
    drawList.addNGonFilled(filledPentagonPosition, 50, kGreen);

    const Cubism::Vec2 filledCirclePosition {100, mHeight / 2 + 100};
    drawList.addCircleFilled(filledCirclePosition, 20, kWhite, 32);

    const Cubism::Vec2 ellipsePosition {300, mHeight / 2 + 100};
    drawList.addEllipse(filledCirclePosition, Cubism::Vec2 {20, 50}, kWhite, 32);

    drawList.addEllipseFilled(invertedMouse, Cubism::Vec2{30, 20}, kRed, 32);

    drawList.addTriangle(Cubism::kZero, invertedMouse, Cubism::Vec2{mWidth, 0.0f}, kBlue);

    const unsigned int fps = (unsigned int)(Cubism::getIO().getFps());
    const std::string fpsStr = "Fps:" + std::to_string(fps);
    drawList.addText(fpsStr, invertedMouse, kGreen, Cubism::kZero, 1.0f);
    
    drawList.addText("the quick brown fox jumps over the lazy dog!", Cubism::kOne, kGreen, Cubism::kZero, 0.3f);

  }
  
  void updateIO(Cubism::IO& io, int width, int height, int windowWidth, int windowHeight)
  {
    mWidth = windowWidth;
    mHeight = windowHeight;
    io.displaySize.x = windowWidth;
    io.displaySize.y = windowHeight;
    if (windowWidth > 0 && windowHeight > 0)
    {
      float xs = width / static_cast<float>(windowWidth);
      float ys = height / static_cast<float>(windowHeight);
      io.displayFramebufferScale.x = xs;
      io.displayFramebufferScale.y = ys;
    }
    io.displayPosition = Cubism::Vec2 {0, 0};
  }
  
private:
  bool mMiddleMousePressed;
  float mLastX;
  float mLastY;
  bool mShiftPressed;
  float mWidth;
  float mHeight;
};

int main()
{
  MainApp app { "Cubism With OpenGL3", kWindowWidth, kWindowHeight, kGlMajor, kGlMinor };
  app.run();
  return EXIT_SUCCESS;
}
