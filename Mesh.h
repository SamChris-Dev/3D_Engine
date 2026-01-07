#pragma once
#include <GL/freeglut.h>
#include <vector>

class Mesh {
protected:
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<float> normals;
    std::vector<unsigned char> indices;
    GLenum primitiveType;

public:
    Mesh(GLenum type = GL_TRIANGLES) : primitiveType(type) {}
    virtual ~Mesh() {}

    void SetVertices(const std::vector<float>& v) { vertices = v; }
    void SetColors(const std::vector<float>& c) { colors = c; }
    void SetNormals(const std::vector<float>& n) { normals = n; }
    void SetIndices(const std::vector<unsigned char>& i) { indices = i; }

    virtual void Draw() { // Standard Draw
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());

        if (!colors.empty()) {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, colors.data());
        }
        if (!normals.empty()) {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, 0, normals.data());
        }

        if (!indices.empty()) {
            glDrawElements(primitiveType, (GLsizei)indices.size(), GL_UNSIGNED_BYTE, indices.data());
        }
        else {
            glDrawArrays(primitiveType, 0, (GLsizei)vertices.size() / 3);
        }

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }
};