#include "Engine.h"
#include <glm/gtc/type_ptr.hpp>

Engine* Engine::instance = nullptr;

Engine::Engine() : windowWidth(800), windowHeight(600),
currentProjection(ProjectionType::PERSPECTIVE), fov(60.0f) {
    instance = this;
}

void Engine::Init(int argc, char** argv, int width, int height, const char* title) {
    windowWidth = width;
    windowHeight = height;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(title);

    glutDisplayFunc(Engine::DisplayCallback);
    glutReshapeFunc(Engine::ReshapeCallback);
    glutKeyboardFunc(Engine::KeyboardCallback);
    glutTimerFunc(16, Engine::TimerCallback, 0);

    glEnable(GL_DEPTH_TEST);

   
    // Position objects
    myCube.position = glm::vec3(-3.0f, 0.0f, 0.0f);

    myPlanet.position = glm::vec3(3.0f, 0.0f, 0.0f);
    myPlanet.scale = glm::vec3(0.5f); // Smaller planet
}

void Engine::Run() { glutMainLoop(); }

void Engine::SetProjection(ProjectionType type) {
    currentProjection = type;
    OnResize(windowWidth, windowHeight); 
}

//  Callbacks 
void Engine::DisplayCallback() { if (instance) instance->OnRender(); }
void Engine::ReshapeCallback(int w, int h) { if (instance) instance->OnResize(w, h); }
void Engine::KeyboardCallback(unsigned char k, int x, int y) { if (instance) instance->OnInput(k, x, y); }
void Engine::TimerCallback(int v) { if (instance) { instance->OnUpdate(); glutTimerFunc(16, TimerCallback, 0); } }

//  Logic 
void Engine::OnResize(int w, int h) {
    windowWidth = w; windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;

    if (currentProjection == ProjectionType::ORTHOGRAPHIC) {
        float size = 10.0f;
        glOrtho(-size * aspect, size * aspect, -size, size, 0.1, 100.0);
    }
    else {
        gluPerspective(fov, aspect, 0.1, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

void Engine::OnInput(unsigned char key, int x, int y) {
    float speed = 0.5f;

    // Camera Controls (WASD)
    if (key == 'w') mainCamera.MoveForward(speed);
    if (key == 's') mainCamera.MoveBackward(speed);
    if (key == 'a') mainCamera.StrafeLeft(speed);
    if (key == 'd') mainCamera.StrafeRight(speed);

    // Object Transformation Control
    if (key == 'q') myCube.rotation.y += 5.0f;
    if (key == 'e') myCube.rotation.y -= 5.0f;

    // Toggle Projections
    if (key == 'p') SetProjection(ProjectionType::PERSPECTIVE);
    if (key == 'o') SetProjection(ProjectionType::ORTHOGRAPHIC);

    if (key == 27) glutLeaveMainLoop();
}

void Engine::OnUpdate() {
    glutPostRedisplay();
}

void Engine::OnRender() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get View Matrix from Camera 
        glm::mat4 view = mainCamera.GetViewMatrix();

    //  1. Primitive Axis 

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
    myAxis.Draw();

    //  2. Spinning Cube 
    // Center object
    myCube.rotation.x += 0.5f; // Constant spin
    myCube.rotation.y += 0.5f;
    myCube.Draw(view);

    //  3. Orbiting Planet 
    // Orbiting sphere on the right 
        static float angle = 0.0f;
    angle += 0.02f; // Slower orbit speed
    myPlanet.position.x = 6.0f * cos(angle);
    myPlanet.position.z = 3.0f * sin(angle);
    myPlanet.Draw(view);

    //  4. Letter E 
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
    glPushMatrix();
    glTranslatef(2.0f, 3.0f, 0.0f);
    myLetter.Draw();
    glPopMatrix();

    //  5. The Teapot 
   
    glPushMatrix();
    glTranslatef(-8.0f, 0.0f, 0.0f); 
    glRotatef(angle * 50.0f, 0.0f, 1.0f, 0.0f); 
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow color
    glutWireTeapot(1.0);             
    glPopMatrix();

    glutSwapBuffers();
}