#pragma once
#include "Shader.h"
#include <glew.h>
#include <freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include "angel/Angel.h"

typedef Angel::vec4 point4;
typedef Angel::vec4 color4;

const int NumTimesToSubdivide = 5;
const int NumTriangles = 4096;  // (4 faces)^(NumTimesToSubdivide + 1)
const int NumVertices = 3 * NumTriangles;

class skydome{
public:
	skydome();

	void draw();
	void update();

	void triangle(const point4& a, const point4& b, const point4& c);
	point4 unit(const point4& p);
	void divide_triangle(const point4& a, const point4& b, const point4& c, int count);

	void tetrahedron(int count);

	void reshape(int width, int height);
	
	//setting maticies
	void setProjection(glm::mat4 i) { shader->use(); shader->setMat4("Projection",i); }
	void setCam(glm::mat4 i) { shader->use(); shader->setMat4("view", i); }

private:

	float timenumber;
	int Index = 0;

	GLuint  ModelView, Projection, time, res;

	GLfloat rot_incr = 0.3;  // angle to increment rotation by each idle tick.
	GLfloat rotation = 0.0; // angle of rotation of view.

	point4 points[NumVertices];
	vec4   normals[NumVertices];


	GLuint vao;
	GLuint buffer;

	Shader* shader;

	// Update the last updated time to now.
	void set_last_time();

	// Reset the simulation time for this object to 0.
	void reset_time();

	// Returns the time since the last update
	GLint compute_time();

	//timing
	GLint last_time;
	GLint current_time;

};

