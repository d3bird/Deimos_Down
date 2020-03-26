#pragma once

#include <glew.h>
#include <freeglut.h>
#include <string>

#include "Shader.h"

class gui{
public:
	//constructors
	gui();
	~gui();

	//functions

	void draw(Shader* input_shader);

	void init();

	void Toggleshow() { hide = !hide; }

	//setters and getters

	//set window height and width
	void setWindowSize(int wheight, int wwidth) { Wheight = wheight; Wwidth = wwidth; }

	void setTexture1(unsigned int i) { texture1 = i; }
	void setTexture2(unsigned int i) { texture2 = i; }
private:
	void setImages();

	bool inited;
	bool hide;
	//window vars
	int Wheight;
	int Wwidth;

	//graphics stuff
	unsigned int VBO, VAO, EBO;
	unsigned int texture1, texture2;

	std::string texPath1;
	std::string texPath2;

	Shader* shader;

};

