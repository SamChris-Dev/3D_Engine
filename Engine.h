#pragma once
#include<Windows.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Camera.h"
#include "PrimitiveObject.h"
#include "Cube.h"
#include "LetterE.h" 

enum class ProjectionType { ORTHOGRAPHIC, PERSPECTIVE };

class Engine {
private:
    int windowWidth, windowHeight;
    ProjectionType currentProjection;
    float fov;

    static Engine* instance;

    //  Camera and Objects
    Camera mainCamera;
    PrimitiveObject myAxis;   
    CubeObject myCube;        
    CubeObject myPlanet;      
    LetterE myLetter;         

    // Callbacks
    static void DisplayCallback();
    static void ReshapeCallback(int w, int h);
    static void KeyboardCallback(unsigned char key, int x, int y);
    static void TimerCallback(int value);

public:
    Engine();
    void Init(int argc, char** argv, int width, int height, const char* title);
    void Run();
    void SetProjection(ProjectionType type);

    // Instance Methods
    void OnRender();
    void OnResize(int w, int h);
    void OnInput(unsigned char key, int x, int y);
    void OnUpdate();
};