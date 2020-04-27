#pragma once

#include <glew.h>
#include <freeglut.h>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "Shader.h"



class gui {
public:
	//constructors
	gui();
	~gui();

	//functions

	void draw();

	void init();

	void Toggleshow() { hide = !hide; }
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);


	//setters and getters

	//set window height and width
	void setWindowSize(int wheight, int wwidth) { Wheight = wheight; Wwidth = wwidth; }


private:

	void setImages();
	void textRenderinginit();
	bool inited;
	bool hide;
	//window vars
	int Wheight;
	int Wwidth;

	//graphics buffers for the shapes 
	unsigned int VBO, VAO, EBO;
	unsigned int texture1, texture2;

	std::string texPath1;
	std::string texPath2;

	Shader* shader;

	//stuff for text rendering
	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};

	bool textworking;
	FT_Library ft;
	FT_Face face;

	std::map<GLchar, Character> Characters;
	glm::mat4 projection;
	Shader* Tshader;
	//grapics buffers for the text
	GLuint tVAO, tVBO;

};

