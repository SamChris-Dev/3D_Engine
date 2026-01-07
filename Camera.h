#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    Camera() {
        position = glm::vec3(0.0f, 2.0f, 10.0f); // High and back
        target = glm::vec3(0.0f, 0.0f, 0.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    glm::mat4 GetViewMatrix() {
       
        return glm::lookAt(position, position + glm::vec3(0, 0, -1), up);
    }

    void MoveForward(float speed) { position.z -= speed; }
    void MoveBackward(float speed) { position.z += speed; }
    void StrafeRight(float speed) { position.x += speed; }
    void StrafeLeft(float speed) { position.x -= speed; }
};