#pragma once
#include <glew.h>
#include "angel/Angel.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef Angel::vec4  point4;
typedef Angel::vec4  color4;

class terrian_obj {
public:

	terrian_obj();
	~terrian_obj();

	void init();
	void draw();
	void update();

	void updateAngle(float i[3]) { theta[0] = i[0]; theta[1] = i[1]; theta[2] = i[2]; }

	//setters for the matrixes
	void setProjectiont(glm::mat4 i) { shader->use(); shader->setMat4("Projection", i); }
	void setVeiw(glm::mat4 i) { shader->use(); shader->setMat4("model_view", i); }
	void setModelTrans(glm::mat4 i) { shader->use(); shader->setMat4("model_trans", i); }


	void setRes(int width, int height) { shader->setVec2("u_resolution",glm::vec2(width, height) ); }

private:

	void colorcube();
	void MyQuad(int a, int b, int c, int d);
	GLuint get_points_size() { return sizeof(points); }

	Shader* shader;
	GLuint vao;
	GLuint buffers[2];
	GLuint Modelview, Projection, ModelTrans;

	const static int NumVertices = 36;
	point4  vertices[8];
	point4 points[NumVertices];
	color4 quad_color[NumVertices];

	vec4 material_diffuse;

	//selected color
	color4 Scolor;
	//rotation angles
	float theta[3];

	color4 outline;
};

