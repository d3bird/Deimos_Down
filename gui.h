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

	void draw(float time);

	void init();

	void Toggleshow();
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);


	//sets the state of the gui to draw different things
	void state_hud() { state = 0; }
	void state_loading() { state = 1; }
	void state_main_menu() { state = 2; }
	void state_options() { state = 3; }

	//set window height and width
	void setWindowSize(int wheight, int wwidth) {
		Wheight = wheight; Wwidth = wwidth; update_shader = true;
	}


private:

	void draw_hud();
	void draw_loading();
	void draw_main_menu();
	void draw_options();

	void update_shader_var();

	void setImages();
	void textRenderinginit();
	bool inited;
	int state;
	int prevState;

	//window vars
	int Wheight;
	int Wwidth;

	bool update_shader;

	//graphics buffers and textures
	unsigned int VBO, VAO, EBO;
	//test textures
	unsigned int texture1; // container
	unsigned int texture2;// face

	unsigned int logo;
	unsigned int title;
	unsigned int loading_screen;

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

