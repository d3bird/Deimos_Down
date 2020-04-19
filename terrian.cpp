#include "terrian.h"


terrian1::terrian1() {
	int width = 135;
	int length = 135;
	int height = 135;
	points_generated = 0;
	// cube dimentions
	vertices[0] = point4(-width, -(height), length, 1.0);
	vertices[1] = point4(-width, (height), length, 1.0);
	vertices[2] = point4(width, (height), length, 1.0);
	vertices[3] = point4(width, -(height), length, 1.0);

	vertices[4] = point4(-width, -(height), -length, 1.0);
	vertices[5] = point4(-width, (height), -length, 1.0);
	vertices[6] = point4(width, (height), -length, 1.0);
	vertices[7] = point4(width, -(height), -length, 1.0);
	
	//createPoints();//ceate the points on the map
	createPoints_strip();
	colorcube();//create the cube points
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
	//draw by indiviual triangles
	//glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	//glDrawArrays(GL_TRIANGLES, NumVertices, NumVertices_map);

	//draw triangle strip in
	glDrawArrays(GL_TRIANGLE_STRIP, NumVertices, points_generated);
}

void terrian1::setupBuffer() {

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

//creates points for use of a sinlge triangle strip
void terrian1::createPoints_strip() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int index = NumVertices;// starting index after  the cube

	int width = 135;
	int length = 135;
	int height = 135;

	int distance_value = 200;
	int start_height = -400;

	points_generated = 4;

	//generates the inital square
	points[index] = point4(0, start_height, 0, 1.0);
	index++;
	points[index] = point4(0, start_height, distance_value, 1.0);
	index++;
	points[index] = point4(distance_value, start_height, 0, 1.0);
	index++;
	points[index] = point4(distance_value, start_height, distance_value, 1.0);
	index++;

	int xoffset = 1;
	int zoffset = 2;

	bool going_right = true;//if the points are being generated to the right/left

	//for (int x = 0; x < grid_height - 1; x++) {
		for (int i = 0; i < grid_width; i++) {
			if (going_right) {
				points[index] = point4(distance_value * xoffset, start_height, 0, 1.0);
				index++;
				points[index] = point4(distance_value * xoffset, start_height, distance_value, 1.0);
				index++;
				points_generated += 2;
				xoffset++;
			}
			else {


			}
		}
		//switch to going the other direction
		if (going_right) {
			//temp
			points[index] = points[index - 3];
			index++;
			xoffset--;
			points[index] = point4(distance_value * xoffset, start_height, 0 + (distance_value*2), 1.0);
			index++;
			points[index] = point4(distance_value * (xoffset-1), start_height, distance_value + (distance_value * 1), 1.0);
			index++;
			points_generated += 3;
			

		}
		else {


		}
		going_right = !going_right;//swap
	//}

	std::cout << points_generated << std::endl;
	std::cout << "points generated " << points_generated << std::endl;
}


//creates points for rendering through glDrawArrays
void terrian1::createPoints() {
	//lines for debugging
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int index = NumVertices;// starting index after  the cube
	
	int width = 135;
	int length = 135;
	int height = 135;
	
	int distance_value = 200;
	int start_height = -400;

	int xoffset = 0;
	int zoffset = 0;
	
	int xoffset_total = ((xoffset * distance_value));
	int zoffset_total = (zoffset * distance_value);
	
	//generates a 16x16 grid
	for (int i = 0; i < num_of_squares; i++) {

		int value1, value2;
		xoffset_total = ((xoffset * distance_value));
		zoffset_total = (zoffset * distance_value);

		points[index] = point4(0 + xoffset_total, start_height, (0 + zoffset_total), 1.0);
		index++;
		points[index] = point4(0 + xoffset_total, start_height, (distance_value + zoffset_total), 1.0);
		value2 = index;
		index++;
		points[index] = point4((distance_value + xoffset_total), start_height, (0 + zoffset_total), 1.0);
		value1 = index;
		index++;

		points[index] = points[value1];
		index++;
		points[index] = point4((distance_value + xoffset_total), start_height, (distance_value + zoffset_total), 1.0);
		index++;
		points[index] = points[value2];
		index++;

		xoffset ++;
		if (xoffset == 16) {
			xoffset = 0;
			zoffset++;
		}
		//std::cout << "created one square, "<< xoffset_total << std::endl;
	}

	raise_square(0, 0, 135);
	raise_square(0, 15, 135);
	//raise_square(15, 0, 135);
	//raise_square(15, 15, 135);
}

//for use with the draw by array
void terrian1::raise_square(int x, int  z, int amount) {
	int g_w = grid_width - 1;
	int g_h = grid_height - 1;
	if (x < 0 || x >grid_width || z < 0 ||z >grid_height) {
		std::cout << "wong parms to raise squares" << std::endl;
		return;
	}
	int offset = (x * 6) + (z * (6 * grid_width));//generates the offset for the square
	int index = NumVertices + offset;//calculates the start point from the cube start point
	points[index].y = points[index].y + amount;
	index++;
	points[index].y = points[index].y + amount;
	index++;
	points[index].y = points[index].y + amount;
	index++;
	points[index].y = points[index].y + amount;
	index++;
	points[index].y = points[index].y + amount;
	index++;
	points[index].y = points[index].y + amount;
	index++;

	index = NumVertices + offset;

	//adjust the surounding squares
	//the square to the left
	if (x != 0) {
		int new_offset = ((x - 1) * 6) + (z * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2 + 2].y = points[index + 2].y;
		points[index2 + 3].y = points[index + 3].y;
		points[index2 + 4].y = points[index + 4].y;
	}
	//the square to the right
	if (x != g_w) {
		int new_offset = ((x + 1) * 6) + (z * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2].y = points[index + 2].y;
		points[index2 + 1].y = points[index + 3].y;
		points[index2 + 5].y = points[index + 4].y;
	}
	//the square bellow
	if (z != 0) {
		int new_offset = ((x) * 6) + ((z + 1) * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2].y = points[index].y;
		points[index2 + 2].y = points[index + 2].y;
		points[index2 + 3].y = points[index + 3].y;
	}
	//the bottom right squre change
	if (z != 0 && x != 0){
		int new_offset = ((x) * 6) + ((z + 1) * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2 + 6].y = points[index + 6].y;
	}
	//the bottom left squre change
	if (z != 0 && x != 0) {
		int new_offset = ((x-1) * 6) + ((z + 1) * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2 + 2].y = points[index + 2].y;
		points[index2 + 3 ].y = points[index +3].y;
	}

	//the square above
	if (z != 0) {
		int new_offset = ((x) * 6) + ((z - 1) * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2+1].y = points[index].y;
		points[index2 + 4].y = points[index + 2].y;
		points[index2 + 5].y = points[index + 3].y;
	}
	//the up right squre change
	if (z != 0 && x != 0) {
		int new_offset = ((x+1) * 6) + ((z - 1) * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2 + 1].y = points[index + 1].y;
		points[index2 + 5].y = points[index + 5].y;
	}
	//the up left squre change
	if (z != 0 && x != 0) {
		int new_offset = ((x - 1) * 6) + ((z - 1) * (6 * grid_width));
		int index2 = NumVertices + new_offset;
		points[index2 +4].y = points[index+4].y;
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