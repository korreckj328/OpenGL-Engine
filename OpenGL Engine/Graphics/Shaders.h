//
// Created by Jeremiah Korreck on 10/20/19.
// Copyright (c) 2019 Korrecksoftware. All rights reserved.
//

#ifndef OPENGL_ENGINE_SHADERS_H
#define OPENGL_ENGINE_SHADERS_H

#include <GL/glew.h>
#include <string.h>
#include <fstream>
#include <sstream>

class Shaders {
public:
    Shaders();
    ~Shaders();
    GLuint GetShaderProgram();
    void Init(const GLchar *vertexPath, const GLchar *fragmentPath);
private:
    GLuint vertexShader;
    GLint success;
    GLchar infoLog[512];
    bool InitializeVertexShader(const GLchar *vertexPath);
    GLuint fragmentShader;
    bool InitializeFragmentShader(const GLchar *vertexPath);
    GLuint shaderProgram;
    bool LinkShaders();

};


#endif //OPENGL_ENGINE_SHADERS_H
