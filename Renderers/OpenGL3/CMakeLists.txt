## Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(CubismRendererOpenGL3)

set(Headers
  ${CMAKE_HOME_DIRECTORY}/Cubism/Cubism.hpp
  ${CMAKE_HOME_DIRECTORY}/Cubism/CubismFont.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CubismOpenGL3.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GlfwApp.hpp
)

set(Sources
  ${CMAKE_HOME_DIRECTORY}/Cubism/Cubism.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CubismOpenGL3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GlfwApp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${Sources} ${Headers})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_HOME_DIRECTORY}/Cubism)

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} glfw)

# gl3w
target_include_directories(${PROJECT_NAME} PUBLIC ${GL3W_HEADER_ROOT_DIR})
target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_HOME_DIRECTORY}/ThirdParty/gl3w/src/gl3w.c)
