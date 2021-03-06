#pragma once
#include <glew.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "gridsegment.h"

typedef Angel::vec4  point4;
typedef Angel::vec4  color4;

class terrian1{
public:
	terrian1();
	~terrian1();

	void draw();


	//setters for the matrixes
	void setProjectiont(glm::mat4 i) { shader->use(); shader->setMat4("Projection", i); }
	void setVeiw(glm::mat4 i) { shader->use(); shader->setMat4("model_view", i); }
	void setModelTrans(glm::mat4 i) { shader->use(); shader->setMat4("model_trans", i); }

	void setRes(int width, int height) { shader->use(); shader->setVec2("u_resolution", glm::vec2(width, height)); }


private:

	int points_generated;

	void createPoints();

	void create_data_structure();

	void mapDebug();
	void raise_map_segment(int xloc,int yloc,int corn, int  amount );
	void setupBuffer();
	void colorcube();
	void MyQuad(int a, int b, int c, int d);

	GLuint get_points_size() { return sizeof(points); }

	gridSegment** map;

	Shader* shader;
	GLuint vao;
	GLuint buffers[2];
	GLuint Modelview, Projection, ModelTrans;

	//the first 36 are reservered to highlight the square
	const static int NumVertices = 36;
	const static int NumVertices_map = 1536;
	int num_of_squares = NumVertices_map / 6;
	int grid_width = 16;
	int grid_height =16;
	
	point4  vertices[8];
	point4 points[NumVertices + NumVertices_map];

	point4* total_points;
	 
};

