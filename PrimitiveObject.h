#pragma once
#include "Mesh.h"

class PrimitiveObject : public Mesh {
public:
    PrimitiveObject() : Mesh(GL_LINES) {
        // Vertices: 3 lines (start, end)
        std::vector<float> v = {
            0.0f, 0.0f, 0.0f,   5.0f, 0.0f, 0.0f, // X Axis
            0.0f, 0.0f, 0.0f,   0.0f, 5.0f, 0.0f, // Y Axis
            0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 5.0f  // Z Axis
        };

        // Colors: R, G, B
        std::vector<float> c = {
            1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f, // Red
            0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f, // Green
            0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f  // Blue
        };

        this->SetVertices(v);
        this->SetColors(c);
    }
};