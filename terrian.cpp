#include "terrian.h"


terrian1::terrian1() {
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
	
	createPoints();//ceate the points on the map
	setupBuffer();//create the buffer
}

terrian1::~terrian1() {
	delete shader;
}

void terrian1::draw() {
	glBindVertexArray(vao);
	shader->use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.27, 0, 0));
	shader->setMat4("model_trans", model);
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	glDrawArrays(GL_TRIANGLES, NumVertices, 6);
}

void terrian1::setupBuffer() {
	colorcube();//create the cube points


	total_points = new point4[NumVertices + NumVertices_map] ;
	for (int i = 0; i < NumVertices; i++) {
		total_points[i] = points[i];
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// set up vertex buffer object

	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, get_points_size(), points, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, (sizeof(total_points)), total_points, GL_STATIC_DRAW);
	std::cout << get_points_size() << std::endl;
	std::cout << (sizeof(total_points)) << std::endl;
	shader = new Shader("terrian.vs", "terrian.fs");
	shader->use();

	GLuint loc = glGetAttribLocation(shader->ID, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	shader->setVec4("objColor", glm::vec4(1.0, 1.0, 0.0, 1.0));
	glBindVertexArray(0);

}

void terrian1::createPoints() {
	//lines for debugging
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int index = NumVertices;// starting index after  the cube
	
	int width = 135;
	int length = 135;
	int height = 135;
	
	int distance_value = 200;
	int start_height = -400;

	int offset_amount = 1;
	
	int num_of_squares = 1;
	for (int i = 0; i < num_of_squares; i++) {
		int value1, value2;
		points[index] = point4(0, start_height, 0, 1.0);
		index++;
		points[index] = point4(0, start_height, distance_value, 1.0);
		value2 = index;
		index++;
		points[index] = point4(distance_value, start_height, 0, 1.0);
		value1 = index;
		index++;

		points[index] = points[value1];
		index++;
		points[index] = point4(distance_value, start_height, distance_value, 1.0);
		index++;
		points[index] = points[value2];
		index++;

	}

}


//creates the points for the highlighting cube
void terrian1::colorcube() {
	MyQuad(1, 0, 3, 2);
	MyQuad(2, 3, 7, 6);
	MyQuad(3, 0, 4, 7);
	MyQuad(6, 5, 1, 2);
	MyQuad(4, 5, 6, 7);
	MyQuad(5, 4, 0, 1);
}

void terrian1::MyQuad(int a, int b, int c, int d) {
	static int i = 0;
	points[i] = vertices[a];
	i++;
	points[i] = vertices[b];
	i++;
	points[i] = vertices[c];
	i++;
	points[i] = vertices[a];
	i++;
	points[i] = vertices[c];
	i++;
	points[i] = vertices[d];
	i++;
	i %= 36;
}