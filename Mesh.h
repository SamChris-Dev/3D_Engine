#pragma once
#include <GL/freeglut.h>
#include <vector>

class Mesh {
protected:
    // Data containers
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<float> normals;
    std::vector<unsigned char> indices; // For indexed drawing

    // State
    GLenum primitiveType; // GL_TRIANGLES, GL_LINES .

public:
    Mesh(GLenum type = GL_TRIANGLES) : primitiveType(type) {}
    virtual ~Mesh() {}

    // Methods to populate data
    void SetVertices(const std::vector<float>& verts) { vertices = verts; }
    void SetColors(const std::vector<float>& cols) { colors = cols; }
    void SetNormals(const std::vector<float>& norms) { normals = norms; }
    void SetIndices(const std::vector<unsigned char>& inds) { indices = inds; }

    //  Drawing logic
    void Draw() {
        //  Enable and Bind Vertex Array  
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());

        //  Enable and Bind Colors 
        if (!colors.empty()) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, colors.data());
        }

        //  Enable and Bind Normals 
        if (!normals.empty()) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, 0, normals.data());
        }

        //  Draw Call 
        if (indices.empty()) {
            // Non-indexed drawing (Lines, Strips, Fans)
            glDrawArrays(primitiveType, 0, vertices.size() / 3);
        }
        else {
            // Indexed drawing (The Cube)
            glDrawElements(primitiveType, indices.size(), GL_UNSIGNED_BYTE, indices.data());
        }

        //  Cleanup
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }
};