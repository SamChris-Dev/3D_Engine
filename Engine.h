#pragma once
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Cube.h"
#include "Camera.h"

enum class ProjectionType {
    ORTHOGRAPHIC,
    PERSPECTIVE
};

class Engine {
    // Members
	//Cube myCube;
    Camera mainCamera;
    CubeObject myCube;
    CubeObject myPlanet;

private:
    // Window settings
    int windowWidth;
    int windowHeight;
    int windowHandle;

    // State
    ProjectionType currentProjection;
    float fov;

	// for static callbacks
    static Engine* instance;

    
    void InitGLUT(int argc, char** argv);
    void UpdateProjection();

    // Static Callbacks 
    static void DisplayCallback();
    static void ReshapeCallback(int w, int h);
    static void KeyboardCallback(unsigned char key, int x, int y);
    static void TimerCallback(int value);

public:
    Engine();
    ~Engine();

    // Initialization and Graphics Mode 
    void Init(int argc, char** argv, int width, int height, const char* title);

    //  Main game loop start 
    void Run();

    //  Support for changing active projection 
    void SetProjection(ProjectionType type);

    //  logic 
    void OnRender();
    void OnResize(int w, int h);
    void OnInput(unsigned char key, int x, int y);
    void OnUpdate();
};
