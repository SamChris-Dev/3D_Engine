#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject {
public:
    // Transformation State
    glm::vec3 position;
    glm::vec3 rotation; // In degrees (x, y, z)
    glm::vec3 scale;

    GameObject() : position(0.0f), rotation(0.0f), scale(1.0f) {}
    virtual ~GameObject() {}

    // Calculate the "Model Matrix" 
    // Order: Translate * Rotate * Scale
    glm::mat4 GetModelMatrix() {
        glm::mat4 model = glm::mat4(1.0f); // Identity matrix [cite: 710]

        // 1. Translation [cite: 608]
        model = glm::translate(model, position);

        // 2. Rotation (Euler Angles) [cite: 606]
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

        // 3. Scaling [cite: 607]
        model = glm::scale(model, scale);

        return model;
    }

    // Pure virtual method - children must implement this
    virtual void Draw(const glm::mat4& viewMatrix) = 0;
};