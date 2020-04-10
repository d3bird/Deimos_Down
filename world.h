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
#include "terrian_obj.h"
#include "terrian.h"

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
	void setScreenSize(int width, int height);
	void importGUI(gui* i) { hud = i; }
	//getters


	//misc functions
	void toggleHud(){ hud->Toggleshow(); }


private:

	void setupModels();
	int debug;// 0 for normal
				// 1 for objects
				// 2 for sky
				//3 for gui
				//4 for terrian

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
	terrian_obj* terrian;
	terrian1* map;
};

