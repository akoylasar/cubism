# Cubsim
Copyright (c) Fouad Valadbeigi (akoylasar@gmail.com)

## Introduction
Cubism is a small C++11 library for drawing 2D primitives with additional text rendering support. It has minimal external dependencies. 
It is inspired by [Dear ImGui](https://github.com/ocornut/imgui).

## Features
- Drawing common 2D primitives
- Text rendering
- OpenGL renderer and an example app.

## Usage
Everything under ```Cubism/``` is core to the library. Additionally you can use one of the renderers provided under ```Examples/``` (currently only OpenGL) or implement your own.

## Running Examples
2. Make sure you also have [cmake](https://cmake.org/download/) installed.
1. Make sure you have [python](https://www.python.org/downloads/) installed. This is because [GL3W](https://github.com/skaslev/gl3w) which the example app uses, requires it.
2. Clone the project:
    ```git clone https://github.com/akoylasar/cubism.git```
3. Make sure you initialise the third party submodules:
    ```git submodule update --init```
4. In the root project direcotry create a folder and run cmake:
    ```mkdir Build ```
    ```cd Build```
    ```cmake -G"Your Favorite Compiler" ..```

The project has only been built with ```XCode``` on OSX and ```MSVC 14```  and ```MSVC 15``` on Windows. 

## Prerequisites
- [cmake](https://cmake.org/download/)
- [python](https://www.python.org/downloads/)
- Any C++11 compliant compiler 

## Copyright
See ```LICENSE.txt```.