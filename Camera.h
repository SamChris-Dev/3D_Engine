#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    Camera() {
        position = glm::vec3(0.0f, 0.0f, 5.0f); // Back 5 units
        target = glm::vec3(0.0f, 0.0f, 0.0f);   // Looking at origin
        up = glm::vec3(0.0f, 1.0f, 0.0f);       // Y is up
    }

    // Returns the View Matrix 
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(position, target, up);
    }

    
    void MoveForward(float speed) { position.z -= speed; }
    void MoveBackward(float speed) { position.z += speed; }
    void StrafeRight(float speed) { position.x += speed; }
    void StrafeLeft(float speed) { position.x -= speed; }
};
