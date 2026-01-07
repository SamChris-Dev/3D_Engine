#include "Engine.h"
#include "PrimitiveObject.h"
#include "Cube.h"
#include "LetterE.h"
#include "Camera.h"


// Instances
PrimitiveObject myAxis;
Cube mySingleCube;
LetterE myLetter;

// Initialize static member
Engine* Engine::instance = nullptr;

Engine::Engine() : windowWidth(800), windowHeight(600),
currentProjection(ProjectionType::PERSPECTIVE), fov(60.0f) {
    instance = this;
}

Engine::~Engine() {
    //  Closing the game and cleaning up memory 
  
}

void Engine::Init(int argc, char** argv, int width, int height, const char* title) {
    windowWidth = width;
    windowHeight = height;

    // Initialization of windowing library 
    glutInit(&argc, argv);

    //  parameters for graphic mode (Double buffering, RGBA, Depth buffer) 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // Window configuration
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    windowHandle = glutCreateWindow(title);

    // Register Static Callbacks
    glutDisplayFunc(Engine::DisplayCallback);
    glutReshapeFunc(Engine::ReshapeCallback);
    glutKeyboardFunc(Engine::KeyboardCallback);

    //  Timer support (start the timer loop)
    glutTimerFunc(16, Engine::TimerCallback, 0); // ~60 FPS

    // Enable Z-buffer (Depth test)
    glEnable(GL_DEPTH_TEST);



    // Setup Cube 1
    myCube.position = glm::vec3(-2.0f, 0.0f, 0.0f);

    // Setup Cube 2 (Planet)
    myPlanet.position = glm::vec3(2.0f, 0.0f, 0.0f);
    myPlanet.scale = glm::vec3(0.5f); // Smaller



}

void Engine::Run() {
    //  Main game loop 
    glutMainLoop();
}

//  Projection Logic  
void Engine::SetProjection(ProjectionType type) {
    currentProjection = type;
    UpdateProjection();
}

void Engine::UpdateProjection() {
    // Switch to Projection Matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)windowWidth / (float)windowHeight;

    if (currentProjection == ProjectionType::ORTHOGRAPHIC) {
       
        float size = 10.0f;
        
        glOrtho(-size * aspect, size * aspect, -size, size, 0.1, 100.0);
    }
    else {
       
        gluPerspective(fov, aspect, 0.1, 100.0);
       
    }

    // Switch back to ModelView for drawing
    glMatrixMode(GL_MODELVIEW);
}

void Engine::DisplayCallback() {
    if (instance) instance->OnRender();
}

void Engine::ReshapeCallback(int w, int h) {
    if (instance) instance->OnResize(w, h);
}

void Engine::KeyboardCallback(unsigned char key, int x, int y) {
    if (instance) instance->OnInput(key, x, y);
}

void Engine::TimerCallback(int value) {
    if (instance) {
        instance->OnUpdate();
        glutTimerFunc(16, Engine::TimerCallback, 0); // Recursively call timer
    }
}



void Engine::OnResize(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h); 
    UpdateProjection();     
}

void Engine::OnInput(unsigned char key, int x, int y) {
    
    float speed = 0.5f;

    // WASD Camera Controls
    if (key == 'w') mainCamera.MoveForward(speed);
    if (key == 's') mainCamera.MoveBackward(speed);
    if (key == 'a') mainCamera.StrafeLeft(speed);
    if (key == 'd') mainCamera.StrafeRight(speed);

    // Cube Controls (Task 3 Extension)
    if (key == 'q') myCube.rotation.y += 5.0f; // Rotate Cube
    if (key == 'e') myCube.rotation.y -= 5.0f;

    //  Support for changing active projection
    if (key == 'p' || key == 'P') {
        SetProjection(ProjectionType::PERSPECTIVE);
        std::cout << "Switched to Perspective" << std::endl;
    }
    else if (key == 'o' || key == 'O') {
        SetProjection(ProjectionType::ORTHOGRAPHIC);
        std::cout << "Switched to Orthographic" << std::endl;
    }
    else if (key == 27) { // ESC key
        //  Closing the game 
        glutLeaveMainLoop();
    }
}

void Engine::OnRender() {
    //  Support for clearing the screen to a given color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Dark Teal
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. Get the Camera Matrix
    glm::mat4 view = mainCamera.GetViewMatrix();

    glLoadIdentity();
    // Move camera back slightly to see objects at (0,0,0)
    glTranslatef(0.0f, 0.0f, -5.0f);

   

    // global rotation to spin the whole scene
    static float angle = 0.0f;
    angle += 1.0f;
    glRotatef(angle, 0.0f, 1.0f, 0.0f);


    // Animate Cube 1 (Spinning in place)
    myCube.rotation.x += 1.0f;
    myCube.rotation.z += 1.0f;

    // Animate Planet (Orbit logic from PDF Example 3) [cite: 819-829]
    // We manually modify the position here to simulate orbit
    myPlanet.position.x = 2.0f * cos(glm::radians(angle));
    myPlanet.position.z = 2.0f * sin(glm::radians(angle));



    //  Primitives 
    // Drawing a coordinate axis at the center
    myAxis.Draw();

    //  The Teapot 
    glPushMatrix();
    glTranslatef(-4.0f, 0.0f, 0.0f); 
	glColor3f(1.0f, 1.0f, 1.0f);   //white color  
    glutWireTeapot(1.5);             
    glPopMatrix();

    //   The Cube 
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f); 
    glScalef(1.5f, 1.5f, 1.5f);     
    mySingleCube.Draw();
    glPopMatrix();

    //   The Composite "E" 
    glPushMatrix();
    glTranslatef(4.0f, 0.0f, 0.0f);  // Position it to the right of the teapot
    myLetter.Draw();                
    glPopMatrix();

    myCube.Draw(view);
    myPlanet.Draw(view);


    glutSwapBuffers(); // Double buffering swap
}

void Engine::OnUpdate() {
    //  Main game loop update logic
    glutPostRedisplay(); // Request a redraw
}