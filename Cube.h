#pragma once
#include"GameObject.h"
#include "Mesh.h"


// Inherits Transform logic (GameObject) and Drawing logic (Mesh)
class CubeObject : public GameObject, public Mesh {
public:
    CubeObject() : Mesh(GL_TRIANGLES) {
       


        // --- 1. Vertices (x, y, z) [cite: 358-377] ---
        // 24 vertices to allow distinct normals for flat shading (4 verts per face * 6 faces)
        std::vector<float> v = {
            // Front Face
            -1.0f, -1.0f,  1.0f,   1.0f, -1.0f,  1.0f,   1.0f,  1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,
            // Back Face
            -1.0f, -1.0f, -1.0f,  -1.0f,  1.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f, -1.0f, -1.0f,
            // Top Face
            -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,
            // Bottom Face
            -1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,   1.0f, -1.0f,  1.0f,  -1.0f, -1.0f,  1.0f,
            // Right Face
             1.0f, -1.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f,  1.0f,  1.0f,   1.0f, -1.0f,  1.0f,
             // Left Face
             -1.0f, -1.0f, -1.0f,  -1.0f, -1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,  -1.0f,  1.0f, -1.0f
        };

        // --- 2. Normals (nx, ny, nz) [cite: 378-389] ---
        // Defines the direction each face is pointing (essential for lighting later)
        std::vector<float> n = {
            // Front (0, 0, 1)
            0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            // Back (0, 0, -1)
            0.0f, 0.0f,-1.0f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,-1.0f,
            // Top (0, 1, 0)
            0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            // Bottom (0, -1, 0)
            0.0f,-1.0f, 0.0f,  0.0f,-1.0f, 0.0f,  0.0f,-1.0f, 0.0f,  0.0f,-1.0f, 0.0f,
            // Right (1, 0, 0)
            1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
            // Left (-1, 0, 0)
            -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
        };

        // --- 3. Colors (r, g, b) [cite: 390-405] ---
        // Generates a pattern so you can distinguish faces/vertices visually
        std::vector<float> c;
        for (int k = 0; k < 24; k++) {
            c.push_back((k % 3 == 0) ? 1.0f : 0.0f); // Red component
            c.push_back((k % 3 == 1) ? 1.0f : 0.0f); // Green component
            c.push_back((k % 3 == 2) ? 1.0f : 0.0f); // Blue component
        }

        // --- 4. Indices (Triangles) [cite: 407-436] ---
        // Defines 2 triangles per face (6 indices per face * 6 faces = 36 indices)
        // Uses standard CCW winding order
        std::vector<unsigned char> i = {
             0, 1, 2,   0, 2, 3,    // Front
             4, 5, 6,   4, 6, 7,    // Back
             8, 9,10,   8,10,11,    // Top
            12,13,14,  12,14,15,    // Bottom
            16,17,18,  16,18,19,    // Right
            20,21,22,  20,22,23     // Left
        };

        // Load the data into the parent Mesh class
        this->SetVertices(v);
        this->SetNormals(n);
        this->SetColors(c);
        this->SetIndices(i);



        // Example initialization for visibility
        this->scale = glm::vec3(1.0f);
    }

    // Implementing the Drawing Logic [cite: 671]
    void Draw(const glm::mat4& viewMatrix) override {
        // 1. Calculate ModelView Matrix = View * Model
        glm::mat4 modelMatrix = GetModelMatrix();
        glm::mat4 modelView = viewMatrix * modelMatrix;

        // 2. Load it into OpenGL [cite: 703-707]
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(modelView));

        // 3. Draw using the base Mesh class
        Mesh::Draw();
    }
};

class Cube : public Mesh {
public:
    Cube() : Mesh(GL_TRIANGLES) {
        //  Vertices (x, y, z)
        // 24 vertices (4 per face * 6 faces)
        std::vector<float> v = {
            // Front Face
            -1.0f, -1.0f,  1.0f,   1.0f, -1.0f,  1.0f,   1.0f,  1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,
            // Back Face
            -1.0f, -1.0f, -1.0f,  -1.0f,  1.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f, -1.0f, -1.0f,
            // Top Face
            -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,
            // Bottom Face
            -1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,   1.0f, -1.0f,  1.0f,  -1.0f, -1.0f,  1.0f,
            // Right Face
             1.0f, -1.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f,  1.0f,  1.0f,   1.0f, -1.0f,  1.0f,
             // Left Face
             -1.0f, -1.0f, -1.0f,  -1.0f, -1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,  -1.0f,  1.0f, -1.0f
        };

        //  Normals (nx, ny, nz) 
        std::vector<float> n = {
            // Front (0, 0, 1)
            0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            // Back (0, 0, -1)
            0.0f, 0.0f,-1.0f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,-1.0f,
            // Top (0, 1, 0)
            0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
            // Bottom (0, -1, 0)
            0.0f,-1.0f, 0.0f,  0.0f,-1.0f, 0.0f,  0.0f,-1.0f, 0.0f,  0.0f,-1.0f, 0.0f,
            // Right (1, 0, 0)
            1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
            // Left (-1, 0, 0)
            -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
        };

        //  Colors (r, g, b) 
        
        std::vector<float> c;
        for (int i = 0; i < 24; i++) {
            c.push_back((i % 3 == 0) ? 1.0f : 0.0f); // Red pattern
            c.push_back((i % 3 == 1) ? 1.0f : 0.0f); // Green pattern
            c.push_back((i % 3 == 2) ? 1.0f : 0.0f); // Blue pattern
        }

        //  Indices  
        std::vector<unsigned char> i = {
             0, 1, 2,   0, 2, 3,    // Front
             4, 5, 6,   4, 6, 7,    // Back
             8, 9,10,   8,10,11,    // Top
            12,13,14,  12,14,15,    // Bottom
            16,17,18,  16,18,19,    // Right
            20,21,22,  20,22,23     // Left
        };

        this->SetVertices(v);
        this->SetNormals(n);
        this->SetColors(c);
        this->SetIndices(i);
    }
};
