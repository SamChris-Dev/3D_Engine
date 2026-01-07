#pragma once
#include "Cube.h" // Reuses Cube for parts

class LetterE {
private:
    CubeObject unitCube;
public:
    void Draw() {
        // Spine
        glPushMatrix();
        glTranslatef(-1.0f, 0.0f, 0.0f); glScalef(0.5f, 4.0f, 0.5f);
        unitCube.Mesh::Draw(); // Call basic draw to avoid overwriting matrix
        glPopMatrix();

        // Top
        glPushMatrix();
        glTranslatef(0.5f, 1.75f, 0.0f); glScalef(2.5f, 0.5f, 0.5f);
        unitCube.Mesh::Draw();
        glPopMatrix();

        // Middle
        glPushMatrix();
        glTranslatef(0.25f, 0.0f, 0.0f); glScalef(2.0f, 0.5f, 0.5f);
        unitCube.Mesh::Draw();
        glPopMatrix();

        // Bottom
        glPushMatrix();
        glTranslatef(0.5f, -1.75f, 0.0f); glScalef(2.5f, 0.5f, 0.5f);
        unitCube.Mesh::Draw();
        glPopMatrix();
    }
};