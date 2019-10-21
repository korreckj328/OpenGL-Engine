//
// Created by Jeremiah Korreck on 10/20/19.
// Copyright (c) 2019 Korrecksoftware. All rights reserved.
//

#ifndef OPENGL_ENGINE_SHADERS_H
#define OPENGL_ENGINE_SHADERS_H

#include <GL/glew.h>

class Shaders {
public:
    Shaders();
    ~Shaders();
    GLuint GetShaderProgram();
    void Init();
private:
    const GLchar *vertexShaderSource = "#version 330 core\n"
                                       "layout ( location = 0 ) in vec3 position;\n"
                                       "void main()\n"
                                       "{\n"
                                       "gl_Position= vec4( position.x, position.y, position.z, 1.0 );\n"
                                       "}";

    const GLchar *fragmentShaderSource = "#version 330 core\n"
                                         "out vec4 color;\n"
                                         "void main() \n"
                                         "{\n"
                                         "color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                                         "}";

    GLuint vertexShader;
    GLint success;
    GLchar infoLog[512];
    bool InitializeVertexShader();
    GLuint fragmentShader;
    bool InitializeFragmentShader();
    GLuint shaderProgram;
    bool LinkShaders();


};


#endif //OPENGL_ENGINE_SHADERS_H
