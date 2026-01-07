#pragma once
#include<Windows.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Camera.h"
#include "PrimitiveObject.h"
#include "Cube.h"
#include "LetterE.h" // Changing from M to E as requested

enum class ProjectionType { ORTHOGRAPHIC, PERSPECTIVE };

class Engine {
private:
    int windowWidth, windowHeight;
    ProjectionType currentProjection;
    float fov;

    static Engine* instance;

    // Lab 09: Camera and Objects
    Camera mainCamera;
    PrimitiveObject myAxis;   // Lab 08 Task 1
    CubeObject myCube;        // Lab 08 Task 2 + Lab 09 Task 3
    CubeObject myPlanet;      // Lab 09 Task 2 (Hierarchy example)
    LetterE myLetter;         // Lab 08 Task 3 (Complex Object)

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