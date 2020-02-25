#include "world.h"


world::world(int w, int h, int image_n) {
	Wwidth = w;
	Wheight = h;
	name = "World1";

	number_images = image_n;
	image_lastused = 0;
    inited = false;

    //create the objects
    sky = new skydome();
    sky->reshape(Wwidth, Wheight);
}

world::~world() {
	delete sky;
	delete hud;
	delete ourModel;
	delete ourShader;
}

void world::draw() {
    sky->draw();
    sky->update();
}


//update functions
void world::update(float deltaTime) {


}

//setters
void world::setImage(unsigned int image, int i) {


}


void world::update_cam(glm::mat4 i) {
    sky->setCam(i);
   // ourShader->setMat4("view", i);
}

void world::update_projectio(glm::mat4 i) {
    sky->setProjection(i);
    //ourShader->setMat4("projection", i);
}


void world::setScreenSize(int width, int height) {
     Wwidth = width;
     Wheight = height;
     sky->reshape(width, height);
}