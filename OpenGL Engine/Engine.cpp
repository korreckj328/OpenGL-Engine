//
// Created by Jeremiah Korreck on 10/20/19.
// Copyright (c) 2019 Korrecksoftware. All rights reserved.
//

#include "Engine.h"

Engine::Engine() {
    InitGLFW();
    myShaders = Shaders();
    myShaders.Init("usr/share/man/man1/Resources/shaders/core.vs", "usr/share/man/man1/Resources/shaders/core.fs");


}

Engine::~Engine() {
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    window = nullptr;
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

bool Engine::InitGLFW() {
    // Init GLFW
    glfwInit( );

    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    // Create a GLFWwindow object that we can use for GLFW's functions
    window = glfwCreateWindow( WIDTH, HEIGHT, "OpenGL Engine", nullptr, nullptr );


    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );

        return false;
    }

    glfwMakeContextCurrent( window );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    // Define the viewport dimensions
    glViewport( 0, 0, screenWidth, screenHeight );

    return true;
}

void Engine::Run() {

    GLfloat vertices[] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom left
                0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//bottom right
                0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,//top
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer( GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );

        // Render
        // Clear the colorbuffer
        glClearColor( WHITE[0], WHITE[1], WHITE[2], WHITE[3] );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram(myShaders.GetShaderProgram());
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers( window );
    }
}


