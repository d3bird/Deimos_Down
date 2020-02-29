#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "gui.h"
#include "Shader.h"
#include "model.h"
#include "skydome.h"


class world{
public:

	world(int w, int h, int image_n);
	~world();

	void draw();


	//update functions
	void update(float deltaTime);
	void update_cam(glm::mat4 i);
	void update_projectio(glm::mat4 i);


	//setters
	void setImage(unsigned int image, int i);
	void setScreenSize(int width, int height);

	//getters


	//misc functions
	void toggleHud(){ hud->Toggleshow(); }


private:

	void setupGUI();
	void setupModels();

	bool inited;
	int Wwidth;
	int Wheight;
	std::string name;

	int number_images;
	int image_lastused;

	std::vector<unsigned int> images;

	Shader* modelShader;
	Model* ourModel;
	Model* ourModel2;
	gui* hud;
	skydome* sky;

};

