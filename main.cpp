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

using std::cout;
using std::endl;

//window vars
int Wheight = 600;
int Wwidth = 800;

unsigned int VBO, VAO, EBO;
unsigned int container, face, logo;

Shader* ourShader;
Camera* cam;
Model* ourModel;
gui* hud;
skydome* sky;

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
    ourShader->setMat4("projection", projection);
    sky->reshape(Wwidth, Wheight);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the window
    //activate the textures

    // bind textures on corresponding texture units
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture1);
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, texture2);
    ////switch to the square vertex buffer
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //ourShader->use();


            // render
        // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    // don't forget to enable shader before setting uniforms
    ourShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Wwidth / (float)Wheight, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    ourShader->setMat4("projection", projection);
    ourShader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));	// it's a bit too big for our scene, so scale it down
    ourShader->setMat4("model", model);
    ourModel->Draw(ourShader);
    */
    //hud->draw(NULL);

    sky->setCam(camera.GetViewMatrix());
    sky->update();
    sky->draw();

    glutSwapBuffers();
}

void idle() {
    static float temp = 0;
    float currentFrame =  glutGet(GLUT_ELAPSED_TIME);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    //cout << deltaTime << endl;
    // camera/view transformation


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, temp * glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ourShader->setMat4("model", model);
    temp+=1.1f;
    if (temp == 360) {
        temp = 0;
    }


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
        hud->Toggleshow();
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
        hud->Toggleshow();
		break;
	case 1:

		break;
	case 3:

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
	glutAddMenuEntry("", 1);
	glutAddMenuEntry("", 3);
	glutAddMenuEntry("", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//creates the buffers 
void init() {

    // load and create a texture 
    // -------------------------
    // texture 1: container
    // ---------
    glGenTextures(1, &logo);
    glBindTexture(GL_TEXTURE_2D, logo);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    std::string textloc = "resources/textures/container.jpg";
    unsigned char* data = stbi_load(textloc.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    stbi_image_free(data);
    // texture 2: containe
// ---------
    glGenTextures(1, &container);
    glBindTexture(GL_TEXTURE_2D, container);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
     textloc = "resources/textures/container.jpg";
     data = stbi_load(textloc.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    stbi_image_free(data);
    // texture 2
     // ---------
    glGenTextures(1, &face);
    glBindTexture(GL_TEXTURE_2D, face);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    textloc = "resources/textures/awesomeface.png";
    data = stbi_load(textloc.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader->use(); // don't forget to activate/use the shader before setting uniforms!

    //needs to add the textures to the gui
    hud->setTexture1(container);
    hud->setTexture2(logo);
    hud->init();
}

//creates the objects that are to be used in the program
void myinit() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glClearColor(0.0, 0.0, 0.0, 1.0); //  background
    glutWarpPointer(Wwidth / 2, Wheight / 2);

    // ourShader = new Shader("texture.vs", "texture.fs");
    ourShader = new Shader("model_loading.vs", "model_loading.fs");
    cam = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));;
    cam->printSpeed();
    //cam->setMovespeed(0.001f);
    cam->printSpeed();
    std::cout << "openGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "glut version " << glutGet(GLUT_VERSION) << std::endl;
    ourShader->use();

    ourModel = new Model("resources/objects/nanosuit/nanosuit.obj");

    hud = new gui();
    sky = new skydome();
    sky->reshape(Wwidth, Wheight);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void mouse_scroll(int xoffset, int yoffset, int temp, int temp2) {
    camera.ProcessMouseScroll(yoffset);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(Wwidth, Wheight);
	glutCreateWindow("0.002");
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

	glewInit();
    myinit();
	init();
	glutMainLoop();
	return(EXIT_SUCCESS);
}