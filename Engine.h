//
// Created by Jeremiah Korreck on 10/20/19.
// Copyright (c) 2019 Korrecksoftware. All rights reserved.
//

#ifndef OPENGL_ENGINE_ENGINE_H
#define OPENGL_ENGINE_ENGINE_H
#ifdef __APPLE__
#include "Shaders.h"
#else

#include "Graphics/Shaders.h"

#endif
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL/SOIL.h>

// GLM
#include <glm/vec3.hpp>

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
    GLuint ebo;
    GLuint texture;
    int textureWidth;
    int textureHeight;
    unsigned char *image;
};


#endif //OPENGL_ENGINE_ENGINE_H
