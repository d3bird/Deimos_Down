#include "terrian_obj.h"


terrian_obj::terrian_obj() {

	theta[0] = 90.0;
	theta[1] = 0.0;
	theta[2] = 0.0;

	material_diffuse = color4(0.0, 0.8, 1.0, 1.0); // color of the cube
	outline = color4(1.0, 1.0, 1.0, 1.0);

	int width = 135;
	int length = 135;
	int height = 135;

	// cube dimentions
	vertices[0] = point4(-width, -(height), length, 1.0);
	vertices[1] = point4(-width, (height), length, 1.0);
	vertices[2] = point4(width, (height), length, 1.0);
	vertices[3] = point4(width, -(height), length, 1.0);

	vertices[4] = point4(-width, -(height), -length, 1.0);
	vertices[5] = point4(-width, (height), -length, 1.0);
	vertices[6] = point4(width, (height), -length, 1.0);
	vertices[7] = point4(width, -(height), -length, 1.0);


	//Scolor = color4(1.0, 0.0, 1.0, 1.0);//light amber
	Scolor = color4(1.0, 0.75, 0.0, 1.0);//light amber
	//Scolor = color4(255.0 / 255.0, 133.0 / 255.0, 3.0 / 255.0, 1.0);//darker orange
	//Scolor = color4(254.0 / 255.0, 178.0 / 255.0, 4.0 / 255.0, 1.0);// orange
	//Scolor = color4(229.0 / 255.0, 148.0 / 255.0, 25.0 / 255.0, 1.0);//golden brown

}


void terrian_obj::MyQuad(int a, int b, int c, int d) {
	static int i = 0;

	quad_color[i] = material_diffuse;
	points[i] = vertices[a];
	i++;
	quad_color[i] = material_diffuse;
	points[i] = vertices[b];
	i++;
	quad_color[i] = material_diffuse;
	points[i] = vertices[c];
	i++;
	quad_color[i] = material_diffuse;
	points[i] = vertices[a];
	i++;
	quad_color[i] = material_diffuse;
	points[i] = vertices[c];
	i++;
	quad_color[i] = material_diffuse;
	points[i] = vertices[d];
	i++;
	i %= 36;
}


void terrian_obj::colorcube() {
	MyQuad(1, 0, 3, 2);
	MyQuad(2, 3, 7, 6);
	MyQuad(3, 0, 4, 7);
	MyQuad(6, 5, 1, 2);
	MyQuad(4, 5, 6, 7);
	MyQuad(5, 4, 0, 1);
}


void terrian_obj::draw() {
	
	glBindVertexArray(vao);
	//glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	shader->use();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices); // the top of the table
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void terrian_obj::update() {


}

void terrian_obj::init() {
	colorcube();//create the cube points

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// set up vertex buffer object

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (get_points_size()), points, GL_STATIC_DRAW);
	std::cout << get_points_size() << std::endl;

	shader = new Shader("terrian.vs", "terrian.fs");
	shader->use();

	GLuint loc = glGetAttribLocation(shader->ID, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	shader->setVec4("objColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
	glBindVertexArray(0);
}