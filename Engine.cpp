#include "Engine.h"
#include "BitmapHandler.h"
#include "TexturedCube.h"
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

   
    //  Lighting Setup
    SetupLighting();


    GLuint texID = BitmapHandler::LoadTexture("brickjpg.jpg");


    // Position objects
    myCube.position = glm::vec3(-3.0f, 0.0f, 0.0f);

    myPlanet.position = glm::vec3(3.0f, 0.0f, 0.0f);
    myPlanet.scale = glm::vec3(0.5f);

    // Setup Textured Cube
    myTextureCube.SetTexture(texID);
    myTextureCube.position = glm::vec3(-7.0f, 3.0f, -4.0f); 

}



//  Implement Phong Lighting Model  
void Engine::SetupLighting() {
    //  Enable Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);       // Turn on the first light "bulb"
    glEnable(GL_NORMALIZE);    

    //  Enable Color Tracking
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //  Set Light 0 Properties (The "Sun")
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Soft background light
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Main directional brightness
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Shiny highlights
    GLfloat position[] = { 0.0f, 5.0f, 5.0f, 1.0f }; // Positioned up and front

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    //  Set Global Model
    GLfloat globalAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    //  Default Shading
    glShadeModel(GL_SMOOTH); // Gouraud Shading 
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

    //  Toggle Shading/Lighting 
    if (key == 'l') {
        isLightingEnabled = !isLightingEnabled;
        if (isLightingEnabled) glEnable(GL_LIGHTING);
        else glDisable(GL_LIGHTING);
        std::cout << "Lighting: " << (isLightingEnabled ? "ON" : "OFF") << std::endl;
    }
    if (key == 'k') {
        isSmoothShading = !isSmoothShading;
        if (isSmoothShading) glShadeModel(GL_SMOOTH);
        else glShadeModel(GL_FLAT); 
        std::cout << "Shading: " << (isSmoothShading ? "SMOOTH" : "FLAT") << std::endl;
    }


    if (key == 27) glutLeaveMainLoop();
}

void Engine::OnUpdate() {
    glutPostRedisplay();
}

void Engine::OnRender() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Darker background to see lights better
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get View Matrix from Camera 
        glm::mat4 view = mainCamera.GetViewMatrix();






    //   Primitive Axis 
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
    myAxis.Draw();

    // Re-enable lighting for 3D objects
    if (isLightingEnabled) glEnable(GL_LIGHTING);

    //   Spinning Cube 
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 }; 
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    myCube.rotation.x += 0.5f; // Constant spin
    myCube.rotation.y += 0.5f;
    myCube.Draw(view);

    //   Orbiting Planet 
    static float angle = 0.0f;
    angle += 0.02f; // Slower orbit speed
    myPlanet.position.x = 6.0f * cos(angle);
    myPlanet.position.z = 3.0f * sin(angle);
    myPlanet.Draw(view);

    //   Letter E 
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(view));
    glPushMatrix();
    glTranslatef(6.0f, 4.0f, -4.0f);
    myLetter.Draw();
    glPopMatrix();

    //   The Teapot 
    glPushMatrix();
    glTranslatef(-8.0f, 0.0f, 0.0f); 
    glRotatef(angle * 50.0f, 0.0f, 1.0f, 0.0f); 

    if (isLightingEnabled)
        glutSolidTeapot(1.0);
    else
        glutWireTeapot(1.0);

    glutWireTeapot(1.0);             
    glPopMatrix();



    //  Textured Cube 
    myTextureCube.rotation.y += 1.0f;
    myTextureCube.Draw(view);


    glutSwapBuffers();
}