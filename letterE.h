#pragma once
#include "Cube.h"

class LetterE {
private:
    Cube unitCube; // Reusing the  Cube

public:
    void Draw() {
        

        //   Vertical Spine
        glPushMatrix();
        glTranslatef(-1.0f, 0.0f, 0.0f); 
        glScalef(0.5f, 4.0f, 0.5f);      
        unitCube.Draw();
        glPopMatrix();

        //  Top Bar 
        glPushMatrix();
        glTranslatef(1.0f, 3.5f, 0.0f);
        glScalef(2.5f, 0.5f, 0.5f);      
        unitCube.Draw();
        glPopMatrix();

        //  Middle Bar 
        glPushMatrix();
        glTranslatef(0.5f, 0.0f, 0.0f);
        glScalef(2.0f, 0.5f, 0.5f);
        unitCube.Draw();
        glPopMatrix();

        //  Bottom Bar 
        glPushMatrix();
        glTranslatef(1.0f, -3.5f, 0.0f);
        glScalef(2.5f, 0.5f, 0.5f);       
        unitCube.Draw();
        glPopMatrix();
    }
};