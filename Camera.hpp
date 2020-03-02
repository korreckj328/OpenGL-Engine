#ifndef OPENGL_ENGINE_CAMERA_H
#define OPENGL_ENGINE_CAMERA_H

#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;  // feild of view

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
     glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
     GLfloat yaw = YAW, 
     GLfloat pitch = PITCH)/*: 
     front(glm::vec3(0.0f, 0.0f, -1.0f)), 
     movementSpeed(SPEED), 
     mouseSensitivity(SENSITIVITY), 
     zoom(ZOOM)*/;

    Camera(GLfloat poxX, GLfloat posY, GLfloat posZ, 
        GLfloat upX, GLfloat upY, GLfloat upZ,
        GLfloat yaw, GLfloat pitch)/*: 
        front ( glm:: vec3(0.0f, 0.0f, -1.0f)), 
        movementSpeed(SPEED),
        mouseSensitivity(SENSITIVITY),
        zoom(ZOOM)*/;    

    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

    void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);

    void ProcessMouseScroll(GLfloat yOffset);

    GLfloat GetZoom();
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;
    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;

    void updateCameraVectors();
};



#endif