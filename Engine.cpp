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

void TrampolineScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    if (GlobalEnginePointer != nullptr) {
        GlobalEnginePointer->glfwScrollCallback(window, xOffset, yOffset);
    }
}

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
    myShaders = Shaders();
    myShaders.Init("Resources/shaders/vertexShader.glsl", "Resources/shaders/fragmentShader.glsl");
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    lastX = WIDTH / 2.0f;
    lastY = HEIGHT / 2.0f;
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    currentFrame = 0.0f;
    GlobalEnginePointer = this;

}

Engine::~Engine() {
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    window = nullptr;
    glDeleteVertexArrays(1, &vao);
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
    glfwSetScrollCallback(window, TrampolineScrollCallback);

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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] =  {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.4f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f),
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    // glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer( GL_ARRAY_BUFFER, vbo);
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // texture loading
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    // glm::mat4 projection(1);
    
    // projection = glm::perspective(45.0f, (GLfloat)screenWidth / screenHeight, 0.1f, 100.0f);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string image1Location = "Resources/textures/image1.jpg";
    image = SOIL_load_image(image1Location.c_str(), &textureWidth, &textureHeight, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

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
        glClearColor( WHITE[0], WHITE[1], WHITE[2], WHITE[3] );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(myShaders.GetShaderProgram(), "my_texture"), 0);

        glUseProgram(myShaders.GetShaderProgram());

        // these need to be in the while loop
        glm::mat4 projection(1);
        glm::mat4 model(1);
        glm::mat4 view(1);

        projection = glm::perspective(camera.GetZoom(), (GLfloat)screenWidth / screenHeight, 0.1f, 100.0f);
        // model = glm::rotate(model, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(0.5f, 1.0f, 0.0f) );
        view = camera.GetViewMatrix();

        GLint modelLocation = glGetUniformLocation(myShaders.GetShaderProgram(), "model");
        GLint viewLocation = glGetUniformLocation(myShaders.GetShaderProgram(), "view");
        GLint projectionLocation = glGetUniformLocation(myShaders.GetShaderProgram(), "projection");
        
        
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vao);

        for (GLuint i = 0; i < (sizeof(cubePositions) / sizeof(cubePositions[0])); i++) {
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers( window );
    }
}


void Engine::DoMovement(){
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
        std::cout << "Up pressed" << std::endl;
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
        std::cout << "Down pressed" << std::endl;
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
        std::cout << "Left pressed" << std::endl;
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_DOWN]) {
        std::cout << "Right pressed" << std::endl;
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

void Engine::glfwScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll(yOffset);
}

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


