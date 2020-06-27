## Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Cubism)

set(CMAKE_CXX_STANDARD 17)

## OpenGL.
find_package(OpenGL REQUIRED)

## glfw Make sure we don't add test, example and documentation projects for GLFW.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw)

## Run glew_gen.py shipped by gl3w to generate the header and source files.
set(GL3W_HEADER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/gl3w/include)
if (NOT GL3W_FILES_GENERATED)
  ## FIXEME(Fouad): Generated files should not pollute the source tree of gl3w.
  execute_process(
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/gl3w/gl3w_gen.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/gl3w
    RESULT_VARIABLE ERROR
  )
  if (ERROR)
    message(FATAL_ERROR "Failed to generate gl3w header." )
  else()
    set(GL3W_FILES_GENERATED ON CACHE INTERNAL "")
  endif()
endif()

add_subdirectory(Renderers)
