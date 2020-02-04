
#include <glew.h>
#include <freeglut.h>
#include <stb_image.h>
#include <iostream>
#include <string>
#include "Shader.h"

//window vars
int Wheight = 600;
int Wwidth = 800;

unsigned int VBO, VAO, EBO;
unsigned int texture1, texture2;

Shader* ourShader;

extern "C" void reshape(int width, int height) {

}

extern "C" void motion(int xpos, int ypos){

	glutPostRedisplay();
}


extern "C" void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear the window
    //activate the textures

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //switch to the square vertex buffer
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    ourShader->use();

    glutSwapBuffers();
}

void idle() {


    glutPostRedisplay();
}

extern "C" void mouse(int btn, int state, int xpos, int ypos) {

	glutPostRedisplay();
}


extern "C" void mykey(unsigned char key, int mousex, int mousey) {
	//float cameraSpeed = 2.5f;
	switch (key){
	case 27://hitting the escape key
	case 'q':
		exit(0);
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
	glutAddMenuEntry("draw table", 0);
	glutAddMenuEntry("draw chair", 1);
	glutAddMenuEntry("draw small table", 3);
	glutAddMenuEntry("game", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//creates the buffers 
void init() {

    // build and compile our shader zprogram
    // ------------------------------------
    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
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

    // texture 2
     // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
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
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);
}

//creates the objects that are to be used in the program
void myinit() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glClearColor(0.0, 0.0, 0.0, 1.0); //  background
    glutWarpPointer(Wwidth / 2, Wheight / 2);

    ourShader = new Shader("texture.vs", "texture.fs");
    std::cout << "openGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "glut version " << glutGet(GLUT_VERSION) << std::endl;

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(Wwidth, Wheight);
	glutCreateWindow("0.001");
	//SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(mykey);
	glutPassiveMotionFunc(motion);
	glutMotionFunc(NULL);
	setupMenu();
	glutMenuStatusFunc(menustatus);

	glewInit();
    myinit();
	init();
	glutMainLoop();
	return(EXIT_SUCCESS);
}