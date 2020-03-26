#include "world.h"

#include <stb_image.h>


world::world(int w, int h, int image_n) {
	Wwidth = w;
	Wheight = h;
	name = "World1";

	number_images = image_n;
	image_lastused = 0;
    inited = false;
    hud = NULL;
    setupModels();
}

world::~world() {
	delete sky;
	delete hud;
	delete ourModel;
	delete modelShader;
}

void world::draw() {
   // glm::mat4 model;
    //for (int i = 0; i < 5; i++) {
      //  model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(i*.27, 0, 0));
        //terrian->setModelTrans(model);
        
      //  terrian->draw();
    //}
    modelShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-4.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
    modelShader->setMat4("model", model);
    ourModel->Draw(modelShader);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    modelShader->setMat4("model", model);
    ourModel2->Draw(modelShader);

    sky->draw();
    //
    if (hud != NULL) {
        hud->draw(NULL);
    }
}


//update functions
void world::update(float deltaTime) {
    sky->update();
}


//creates and inits the 3d models
void world::setupModels() {
    terrian = new terrian_obj();
    terrian->init();
    terrian->setRes(Wwidth, Wheight);
    //create the skydome
    sky = new skydome();
    sky->reshape(Wwidth, Wheight);

    //create the differnt shades for the models
    modelShader = new Shader("model_loading.vs", "model_loading.fs");
    modelShader->use();
    //create the nano suit model
    ourModel = new Model("resources/objects/nanosuit/nanosuit.obj");
    ourModel2 = new Model("resources/objects/man/model.dae");
  
}

//update all of the shaders with the cameria change
void world::update_cam(glm::mat4 i) {
   sky->setCam(i);
    terrian->setVeiw(i);
    modelShader->use();
    modelShader->setMat4("view",i);
}

//update the projection matrix of all the shaders
void world::update_projectio(glm::mat4 i) {
    sky->setProjection(i);
    terrian->setProjectiont(i);
    modelShader->use();
    modelShader->setMat4("projection", i);
}

//update thescreen size varibles for all the objects that depend on them
void world::setScreenSize(int width, int height) {
     Wwidth = width;
     Wheight = height;
     sky->reshape(Wwidth, Wheight);
     terrian->setRes(Wwidth, Wheight);
}