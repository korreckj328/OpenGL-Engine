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

#include "Camera.hpp"


class Engine {
public:
    Engine();
    ~Engine();
    void Run();
    void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
    void glfwScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
    void glfwMouseCallback(GLFWwindow *window, double xPos, double yPos);
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
    // GLuint ebo;
    GLuint texture;
    int textureWidth;
    int textureHeight;
    unsigned char *image;
    void DoMovement();

    Camera camera;
    GLfloat lastX;
    GLfloat lastY;
    GLfloat deltaTime;
    GLfloat lastFrame;
    GLfloat currentFrame;

    const int KEYS_SIZE = 1024;
    bool *keys = nullptr;
    bool firstMouse = true;

    
};




#endif //OPENGL_ENGINE_ENGINE_H
