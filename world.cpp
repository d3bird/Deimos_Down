#include "world.h"

#include <stb_image.h>


world::world(int w, int h, int image_n) {
	Wwidth = w;
	Wheight = h;
	name = "World1";

	number_images = image_n;
	image_lastused = 0;
    inited = false;

    setupGUI();
    setupModels();
}

world::~world() {
	delete sky;
	delete hud;
	delete ourModel;
	delete modelShader;
}

void world::draw() {


    modelShader->use();
    ourModel->Draw(modelShader);

    sky->draw();
    

    hud->draw(NULL);
}


//update functions
void world::update(float deltaTime) {
    sky->update();
    modelShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-4.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
    modelShader->setMat4("model", model);
}



void world::setupGUI() {

    hud = new gui();
    unsigned int container, face, logo;
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
    //ourShader->use(); // don't forget to activate/use the shader before setting uniforms!

    //needs to add the textures to the gui
    hud->setTexture1(container);
    hud->setTexture2(logo);
    hud->init();

}

//creates and inits the 3d models
void world::setupModels() {
    //create the skydome
    sky = new skydome();
    sky->reshape(Wwidth, Wheight);

    //create the differnt shades for the models
    modelShader = new Shader("model_loading.vs", "model_loading.fs");
    modelShader->use();
    //create the nano suit model
    ourModel = new Model("resources/objects/nanosuit/nanosuit.obj");
}

//update all of the shaders with the cameria change
void world::update_cam(glm::mat4 i) {
    sky->setCam(i);
    modelShader->use();
    modelShader->setMat4("view",i);
}

//update the projection matrix of all the shaders
void world::update_projectio(glm::mat4 i) {
    sky->setProjection(i);
    modelShader->use();
    modelShader->setMat4("projection", i);
}

//update thescreen size varibles for all the objects that depend on them
void world::setScreenSize(int width, int height) {
     Wwidth = width;
     Wheight = height;
     sky->reshape(width, height);
}