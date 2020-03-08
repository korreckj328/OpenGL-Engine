//
// Created by Jeremiah Korreck on 10/20/19.
// Copyright (c) 2019 Korrecksoftware. All rights reserved.
//
#include <SOIL/SOIL.h>
#include "Engine.h"
#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine *GlobalEnginePointer = nullptr;

void TrampolineKeyCallback(GLFWwindow *a, int b, int c, int d, int e) {
    if (GlobalEnginePointer != nullptr) {
        GlobalEnginePointer->glfwKeyCallback(a,b,c,d,e);
    }
}
// Commenting this out but leaving it intact for potential later use
// void TrampolineScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
//     if (GlobalEnginePointer != nullptr) {
//         GlobalEnginePointer->glfwScrollCallback(window, xOffset, yOffset);
//     }
// }

void TrampolineMouseCallback(GLFWwindow *window, double xPos, double yPos) {
    if (GlobalEnginePointer != nullptr) {
        GlobalEnginePointer->glfwMouseCallback(window,xPos,yPos);
    }
}


Engine::Engine() {
    keys = new bool[KEYS_SIZE];
    for (int i = 0; i < KEYS_SIZE; i++) {
        keys[i] = false;
    }
    InitGLFW();
    
    lightingShaders = Shaders();
    lightingShaders.Init("Resources/shaders/lightingVertexShader.glsl", "Resources/shaders/lightingFragmentShader.glsl");

    lampShaders = Shaders();
    lampShaders.Init("Resources/shaders/lampVertexShader.glsl", "Resources/shaders/lampFragmentShader.glsl");

    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    lastX = WIDTH / 2.0f;
    lastY = HEIGHT / 2.0f;
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    currentFrame = 0.0f;
    GlobalEnginePointer = this;
    lightPos = glm::vec3(1.2f, 1.0f, 2.0f );

}

Engine::~Engine() {
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    window = nullptr;
    glDeleteVertexArrays(1, &boxVao);
    glDeleteBuffers(1, &vbo);
    // glDeleteBuffers(1, &ebo);
    keys = nullptr;
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
    
    glfwSetKeyCallback(window, TrampolineKeyCallback);
    glfwSetCursorPosCallback(window, TrampolineMouseCallback);
    // Commenting this out but leaving it intact for potential later use
    // glfwSetScrollCallback(window, TrampolineScrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    // enabling depth
    glEnable( GL_DEPTH_TEST );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    return true;
}

void Engine::Run() {

    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // This is the box that will be in the "scene"
    glGenVertexArrays(1, &boxVao);
    glGenBuffers(1, &vbo);
    // glGenBuffers(1, &ebo);

    glBindVertexArray(boxVao);

    glBindBuffer( GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    
    
    // this is the light in the scene
    glGenVertexArrays(1, &lightVao);
    glGenBuffers(1, &vbo);
    // glGenBuffers(1, &ebo);

    glBindVertexArray(lightVao);

    glBindBuffer( GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    

//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    glm::mat4 projection(1);
    projection = glm::perspective(camera.GetZoom(), (GLfloat)screenWidth / screenHeight, 0.1f, 100.0f);
    
    
    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents( );
        DoMovement();
        // Render
        // Clear the colorbuffer
        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // glUseProgram(myShaders.GetShaderProgram());
        lightingShaders.Use()
        GLint objectColorLoc = glGetUniformLocation(lightingShaders.GetShaderProgram, "objectColor");
        GLint lightColorLoc = glGetUniformLocation(lightingShaders.GetShaderProgram, "lightColor");

        
        // Swap the screen buffers
        glfwSwapBuffers( window );
    }
}


void Engine::DoMovement(){
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
} 

void Engine::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if(GLFW_KEY_ESCAPE == key && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024) {
        if (GLFW_PRESS == action) {
            keys[key] = true;
        } else if (GLFW_RELEASE == action) {
            keys[key] = false;
        }
    }
    this->DoMovement();
}

// Commenting this out but leaving it intact for potential later use
// void Engine::glfwScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
//     camera.ProcessMouseScroll(yOffset);
// }

void Engine::glfwMouseCallback(GLFWwindow *window, double xPos, double yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement(xOffset, yOffset);
}


