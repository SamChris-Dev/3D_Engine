#pragma once
#include "GameObject.h"
#include "Mesh.h"

class TexturedCube : public GameObject, public Mesh {
private:
    GLuint textureID;

public:
    TexturedCube() : Mesh(GL_TRIANGLES), textureID(0) {
        //  Vertices 
        std::vector<float> v = {
            -1,-1, 1,  1,-1, 1,  1, 1, 1, -1, 1, 1, // Front
            -1,-1,-1, -1, 1,-1,  1, 1,-1,  1,-1,-1, // Back
            -1, 1,-1, -1, 1, 1,  1, 1, 1,  1, 1,-1, // Top
            -1,-1,-1,  1,-1,-1,  1,-1, 1, -1,-1, 1, // Bottom
             1,-1,-1,  1, 1,-1,  1, 1, 1,  1,-1, 1, // Right
            -1,-1,-1, -1,-1, 1, -1, 1, 1, -1, 1,-1  // Left
        };

        //  Normals 
        std::vector<float> n = {
             0, 0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,
             0, 0,-1,  0, 0,-1,  0, 0,-1,  0, 0,-1,
             0, 1, 0,  0, 1, 0,  0, 1, 0,  0, 1, 0,
             0,-1, 0,  0,-1, 0,  0,-1, 0,  0,-1, 0,
             1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,
            -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0
        };

        //  TEXTURE COORDINATES 
        // Mapping the 2D image to each 3D face
        std::vector<float> t;
        for (int k = 0; k < 6; k++) { // For each of the 6 faces
            t.push_back(0.0f); t.push_back(0.0f); // Bottom-Left
            t.push_back(1.0f); t.push_back(0.0f); // Bottom-Right
            t.push_back(1.0f); t.push_back(1.0f); // Top-Right
            t.push_back(0.0f); t.push_back(1.0f); // Top-Left
        }

        //  Indices
        std::vector<unsigned char> i = {
             0, 1, 2,  0, 2, 3,  4, 5, 6,  4, 6, 7,
             8, 9,10,  8,10,11, 12,13,14, 12,14,15,
            16,17,18, 16,18,19, 20,21,22, 20,22,23
        };

        SetVertices(v);
        SetNormals(n);
        SetTexCoords(t); // Set the UVs
        SetIndices(i);
    }

    void SetTexture(GLuint id) { textureID = id; }

    void Draw(const glm::mat4& viewMatrix) override {
        // Calculate matrices
        glm::mat4 modelView = viewMatrix * GetModelMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(modelView));

        // Enable 2D Texturing and Bind the specific image
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glColor3f(1.0f, 1.0f, 1.0f);

        Mesh::Draw();

        // Disable to not affect other objects
        glDisable(GL_TEXTURE_2D);
    }
};