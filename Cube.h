#pragma once
#include "GameObject.h"
#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

class CubeObject : public GameObject, public Mesh {
public:
    CubeObject() : Mesh(GL_TRIANGLES) {
        // Raw Data 
        std::vector<float> v = {
            -1,-1, 1,  1,-1, 1,  1, 1, 1, -1, 1, 1, // Front
            -1,-1,-1, -1, 1,-1,  1, 1,-1,  1,-1,-1, // Back
            -1, 1,-1, -1, 1, 1,  1, 1, 1,  1, 1,-1, // Top
            -1,-1,-1,  1,-1,-1,  1,-1, 1, -1,-1, 1, // Bottom
             1,-1,-1,  1, 1,-1,  1, 1, 1,  1,-1, 1, // Right
            -1,-1,-1, -1,-1, 1, -1, 1, 1, -1, 1,-1  // Left
        };
        std::vector<float> n = {
             0, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,
             0, 0,-1,  0, 0,-1,  0, 0,-1,  0, 0,-1,
             0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0,
             0,-1, 0,  0,-1, 0,  0,-1, 0,  0,-1, 0,
             1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,
            -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0
        };
        std::vector<float> c; // Colorful pattern
        for (int k = 0; k < 24; k++) {
            c.push_back((k % 3 == 0) ? 1.0f : 0.0f);
            c.push_back((k % 3 == 1) ? 1.0f : 0.0f);
            c.push_back((k % 3 == 2) ? 1.0f : 0.0f);
        }
        std::vector<unsigned char> i = {
             0, 1, 2,  0, 2, 3,  4, 5, 6,  4, 6, 7,
             8, 9,10,  8,10,11, 12,13,14, 12,14,15,
            16,17,18, 16,18,19, 20,21,22, 20,22,23
        };

        SetVertices(v); SetNormals(n); SetColors(c); SetIndices(i);
    }

    void Draw(const glm::mat4& viewMatrix) override {
        glm::mat4 modelView = viewMatrix * GetModelMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(modelView));
        Mesh::Draw();
    }
};