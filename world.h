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


private:
	bool inited;
	int Wwidth;
	int Wheight;
	std::string name;

	int number_images;
	int image_lastused;

	std::vector<unsigned int> images;

	Shader* ourShader;
	Model* ourModel;
	gui* hud;
	skydome* sky;

};

