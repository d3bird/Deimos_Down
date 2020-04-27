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
     modelShader = NULL;
     ourModel = NULL;
     ourModel2 = NULL;
     hud = NULL;
     sky = NULL;


    debug = 4;//change this bit to debug different sections

    setupModels();
}

world::~world() {
	delete sky;
	delete hud;
	delete ourModel;
	delete modelShader;
}

void world::draw() {
    glm::mat4 model;
    if (debug == 1) {

        modelShader->use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-4.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        modelShader->setMat4("model", model);
        ourModel->Draw(modelShader);


        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        modelShader->setMat4("model", model);
        ourModel2->Draw(modelShader);
    }
    else if (debug == 2) {
        sky->draw();
    }
    else if (debug == 3) {
        if (hud != NULL) {
            glEnable(GL_BLEND);
            hud->draw(NULL);
            glDisable(GL_BLEND);
        }
    }
    else if (debug == 4) {

        map->draw();
    }
    else {
        modelShader->use();
        model = glm::mat4(1.0f);
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

        if (hud != NULL) {
            glEnable(GL_BLEND);
            hud->draw(NULL);
            glDisable(GL_BLEND);
        }
    }
}


//update functions
void world::update(float deltaTime) {
    if (debug == 0 || debug == 2) {
        sky->update();
    }
}


//creates and inits the 3d models
void world::setupModels() {
    if (debug == 0) {
        
        map = new terrian1();
        map->setRes(Wwidth, Wheight);
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
    else if (debug == 1) {
        //create the differnt shades for the models
        modelShader = new Shader("model_loading.vs", "model_loading.fs");
        modelShader->use();
        //create the nano suit model
        ourModel = new Model("resources/objects/nanosuit/nanosuit.obj");
        ourModel2 = new Model("resources/objects/man/model.dae");
    }else if (debug == 2) {
        sky = new skydome();
        sky->reshape(Wwidth, Wheight);
    }
    else if (debug == 4) {
        map = new terrian1();
        map->setRes(Wwidth, Wheight);
    }
}

//update all of the shaders with the cameria change
void world::update_cam(glm::mat4 i) {
    if (debug == 0) {
        sky->setCam(i);
        modelShader->use();
        modelShader->setMat4("view", i);
    }
    else if (debug == 1) {
        modelShader->use();
        modelShader->setMat4("view", i);
    }
    else if (debug == 2) {
        sky->setCam(i);
    }
    else if (debug == 4) {
        map->setVeiw(i);
    }
}

//update the projection matrix of all the shaders
void world::update_projectio(glm::mat4 i) {
    if (debug == 0) {
        sky->setProjection(i);
        modelShader->use();
        modelShader->setMat4("projection", i);
    }
    else if (debug == 1) {
        modelShader->use();
        modelShader->setMat4("projection", i);
    }
    else if (debug == 2) {
        sky->setProjection(i);
    }
    else if (debug == 4) {
        map->setProjectiont(i);
    }
}

//update thescreen size varibles for all the objects that depend on them
void world::setScreenSize(int width, int height) {
     Wwidth = width;
     Wheight = height;
     if (debug == 0) {
         sky->reshape(Wwidth, Wheight);
     }
     else if (debug == 2) {
         sky->reshape(Wwidth, Wheight);
     }
     else if (debug == 4) {
         map->setRes(Wwidth, Wheight);
     }
}


