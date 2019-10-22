//
// Created by Jeremiah Korreck on 10/20/19.
// Copyright (c) 2019 Korrecksoftware. All rights reserved.
//

#ifndef OPENGL_ENGINE_ENGINE_H
#define OPENGL_ENGINE_ENGINE_H

#include "Shaders.h"
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>



class Engine {
public:
    Engine();
    ~Engine();
    void Run();
private:
    Shaders myShaders;
    const GLint WIDTH = 800;
    const GLint HEIGHT = 600;
    bool InitGLFW();
    GLFWwindow *window = nullptr;
    int screenWidth;
    int screenHeight;
    const float RED[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    const float WHITE[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLuint vbo;
    GLuint vao;
};


#endif //OPENGL_ENGINE_ENGINE_H
