//
// Created by Jeremiah Korreck on 10/20/19.
// Copyright (c) 2019 Korrecksoftware. All rights reserved.
//
#include <iostream>
#include "Shaders.h"

void Shaders::Init() {
    bool result;
    result = InitializeVertexShader();
    if (!result) {
        exit(-1);
    }
    result = InitializeFragmentShader();
    if (!result) {
        exit(-1);
    }
    result = LinkShaders();
    if (!result) {
        exit(-1);
    }

}

Shaders::~Shaders() {

}

bool Shaders::InitializeVertexShader() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shaders::InitializeFragmentShader() {
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shaders::LinkShaders() {
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

GLuint Shaders::GetShaderProgram() {
    return shaderProgram;
}

Shaders::Shaders() {

}
