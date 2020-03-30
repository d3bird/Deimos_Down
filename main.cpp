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

using std::cout;
using std::endl;

//window vars
int Wheight = 600;
int Wwidth = 800;

unsigned int VBO, VAO, EBO;

Camera* cam;
world* World;
sound_engine* sound;
gui* GUI;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = Wheight / 2.0f;
float lastY = Wwidth / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


extern "C" void reshape(int width, int height) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Wwidth / (float)Wheight, 0.1f, 100.0f);
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

    camera.ProcessMouseMovement(xoffset, yoffset);
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

   World->update_cam(camera.GetViewMatrix());
    World->update(deltaTime);
    glutPostRedisplay();
}

//if the mouse was clicked
extern "C" void mouse(int btn, int state, int xpos, int ypos) {
	glutPostRedisplay();
}


extern "C" void mykey(unsigned char key, int mousex, int mousey) {
	//float cameraSpeed = 2.5f;
    switch (key) {
    case 27://hitting the escape key
    case 'q':
        exit(0);
        break;
    case 'w':
        camera.ProcessKeyboard(FORWARD, deltaTime);
        break;
    case 's':
        camera.ProcessKeyboard(BACKWARD, deltaTime);
        break;
    case 'a':
        camera.ProcessKeyboard(LEFT, deltaTime);
        break;
    case 'd':
        camera.ProcessKeyboard(RIGHT, deltaTime);
        break;
    case '1':
        World->toggleHud();
        break;
    default:
        // glutSetWindowTitle(key);
        break;
    }

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
	case 4:

		break;
	case 5:

		break;
	default:
		break;
	}
	glutPostRedisplay();
}

// Create menu items
void setupMenu() {
	glutCreateMenu(myMenu);
	glutAddMenuEntry("toggle images", 0);
	glutAddMenuEntry("toggle line draw", 1);
	glutAddMenuEntry("toggle fill draw", 3);
	glutAddMenuEntry("", 4);
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

    cam = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));;
    cam->printSpeed();

    std::cout << "openGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "glut version " << glutGet(GLUT_VERSION) << std::endl;

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Wwidth / (float)Wheight, 0.1f, 100.0f);

    World = new world(Wwidth, Wheight, 2);
    World->update_cam(camera.GetViewMatrix());
    World->update_projectio(projection);
    GUI = new gui();
    GUI->setWindowSize(Wwidth, Wheight);
    GUI->init();
    World->importGUI(GUI);
    

    //sound = new sound_engine();

}

void mouse_scroll(int xoffset, int yoffset, int temp, int temp2) {
    camera.ProcessMouseScroll(yoffset);
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
	glutMainLoop();
	return(EXIT_SUCCESS);
}