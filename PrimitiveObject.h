#pragma once
#include "Mesh.h"

class PrimitiveObject : public Mesh {
public:
    PrimitiveObject() : Mesh(GL_LINES) {
        std::vector<float> v = { 0,0,0, 5,0,0,  0,0,0, 0,5,0,  0,0,0, 0,0,5 };
        std::vector<float> c = { 1,0,0, 1,0,0,  0,1,0, 0,1,0,  0,0,1, 0,0,1 };
        SetVertices(v); SetColors(c);
    }
};