#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch): 
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(SPEED),
        mouseSensitivity(SENSITIVITY),
        zoom(ZOOM) {

    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    this->updateCameraVectors();

}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, 
        GLfloat upX, GLfloat upY, GLfloat upZ,
        GLfloat yaw, GLfloat pitch): front ( glm:: vec3(0.0f, 0.0f, -1.0f)), 
        movementSpeed(SPEED),
        mouseSensitivity(SENSITIVITY),
        zoom(ZOOM) {

    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    this->updateCameraVectors();

}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
    GLfloat velocity = this->movementSpeed * deltaTime;
    switch (direction) {
        case FORWARD:
            this->position += this->front * velocity;
            break;
        case BACKWARD:
            this->position -= this->front * velocity;
            break;
        case LEFT:
            this->position -= this->right * velocity;
            break;
        case RIGHT:
            this->position += this->right * velocity;
            break;
    }
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
    xOffset *= this->mouseSensitivity;
    yOffset *= this->mouseSensitivity;
    this->yaw += xOffset;
    this->pitch += yOffset;

    if (constrainPitch) {
        if (this->pitch > 89.0f) {
            this->pitch = 89.0f;
        } else if (this->pitch < -89.0f) {
            this->pitch = -89.0f;
        }
    }

    this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yOffset) {
    // This space is for any wanted activity with the scroll wheel
    // currently I have no feature that I'd actually want to implement 
    // here.  But I left the callbacks intact from the tutorial on setting them up
    // so that I would have them for reference if I decide to implement something
    // for this
}

GLfloat Camera::GetZoom() {
    return this->zoom;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}