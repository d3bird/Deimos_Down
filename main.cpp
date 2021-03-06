#include <glew.h>
#include <freeglut.h>
#include <stb_image.h>
#include <iostream>
#include <string>
#include "gui.h"
#include "Shader.h"
#include "camera.h"
#include "model.h"
#include "mesh.h"
#include "skydome.h"
#include "world.h"
#include "sound_engine.h"
#include "keyboard.h"

using std::cout;
using std::endl;

//window vars
int Wheight = 600;
int Wwidth = 800;

unsigned int VBO, VAO, EBO;

world* World;
sound_engine* sound;
gui* GUI;
// camera
Camera* camera;
keyboard* input;

float lastX = Wheight / 2.0f;
float lastY = Wwidth / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


extern "C" void reshape(int width, int height) {
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)Wwidth / (float)Wheight, 0.1f, 100.0f);
    World->setScreenSize(Wwidth, Wheight);
    World->update_projectio(projection);
}

//if the mouse was moved
extern "C" void motion(int xpos, int ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
	glutPostRedisplay();
}


extern "C" void display() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // GUI->draw(NULL);
    World->draw();
    glutSwapBuffers();
}

void idle() {
    static float temp = 0;
    float currentFrame =  glutGet(GLUT_ELAPSED_TIME);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    //cout << deltaTime << endl;

   World->update_cam(camera->GetViewMatrix());
   World->update(deltaTime);
   glutPostRedisplay();
}

//if the mouse was clicked
extern "C" void mouse(int btn, int state, int xpos, int ypos) {
	glutPostRedisplay();
}


extern "C" void mykey(unsigned char key, int mousex, int mousey) {
    input->upadate_time(deltaTime);
    input->process_key(key, mousex, mousey);
    return;
}

extern "C" void menustatus(int status, int x, int y) {
	
	glutPostRedisplay();
}

extern "C" void myMenu(int value) {
	switch (value) {
	case 0:
      //  World->toggleHud();
		break;
	case 1:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 3:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
	default:
		break;
	}
	glutPostRedisplay();
}

extern "C" void guiMenu(int value) {
    switch (value) {
    case 0:
        GUI->state_hud();
        break;
    case 1:
        GUI->state_main_menu();
        break;
    case 2:
        GUI->state_options();
        break;
    case 3:
        GUI->state_loading();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// Create menu items
void setupMenu() {

    int guimenu = glutCreateMenu(guiMenu);
    glutAddMenuEntry("draw hud", 0);
    glutAddMenuEntry("draw main menu", 1);
    glutAddMenuEntry("draw options menu", 2);
    glutAddMenuEntry("draw loading screen", 3);

	int main = glutCreateMenu(myMenu);
	glutAddMenuEntry("toggle line draw", 1);
	glutAddMenuEntry("toggle fill draw", 3);
    glutAddSubMenu("gui options", guimenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//creates the buffers 
void init() {

    
}

//creates the objects that are to be used in the program
void myinit() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glClearColor(0.0, 0.0, 0.0, 1.0); //  background
    glutWarpPointer(Wwidth / 2, Wheight / 2);

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    std::cout << "openGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "glut version " << glutGet(GLUT_VERSION) << std::endl;

    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)Wwidth / (float)Wheight, 0.1f, 100.0f);

    World = new world(Wwidth, Wheight, 2);
    World->update_cam(camera->GetViewMatrix());
    World->update_projectio(projection);
    GUI = new gui();
    GUI->setWindowSize(Wwidth, Wheight);
    GUI->init();
    World->importGUI(GUI);
    
    std::cout << "creating keyboard layout" << std::endl;
    //sound = new sound_engine();
    input = new keyboard(camera);
}

void mouse_scroll(int xoffset, int yoffset, int temp, int temp2) {
    camera->ProcessMouseScroll(yoffset);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(Wwidth, Wheight);
	glutCreateWindow("0.003");
	//SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(mykey);
	glutPassiveMotionFunc(motion);
	glutMotionFunc(NULL);
    glutMouseWheelFunc(mouse_scroll);
	setupMenu();
	glutMenuStatusFunc(menustatus);
    //glutFullScreen();
	glewInit();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
    myinit();
	init();
    glDisable(GL_BLEND);
	glutMainLoop();
	return(EXIT_SUCCESS);
}