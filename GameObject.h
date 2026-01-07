#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    GameObject() : position(0.0f), rotation(0.0f), scale(1.0f) {}
    virtual ~GameObject() {}

    glm::mat4 GetModelMatrix() {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, scale);
        return model;
    }

    virtual void Draw(const glm::mat4& viewMatrix) = 0;
};