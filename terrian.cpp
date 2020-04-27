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
	
	create_data_structure();
	createPoints();
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

//creates points for use of a sinlge triangle strip for the terrian
void terrian1::createPoints() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//vars to create the map api
	int x = 0;
	int z = 0;
	int points_start = -1;
	int points_end = -1;
	int nw = -1;
	int ne = -1;
	int sw = -1;
	int se = -1;
	int amt_thr_pnts = -1;
	int* otherpoints = NULL;

	//map[x][z] = gridSegment(points_start, points_end, x, z, nw, ne, sw, se, amt_thr_pnts, otherpoints);
	int index = NumVertices;// starting index after  the cube

	int width = 135;
	int length = 135;
	int height = 135;

	int distance_value = 200;// *sin();
	int start_height = -400;

	int xoffset = 0;
	int zoffset = 0;

	bool go_right = true;

	bool going_left = false;
	bool going_right = false;
	bool first_turn = true;
	//equations to calc the offsets value
	int xoffset_amount = xoffset * distance_value;
	int zoffset_amount = zoffset * distance_value;

	points_start = index;
	points_end = index;

	//create the base square
	points[index] = point4(0, start_height, 0, 1.0);
	nw = index;
	index++;
	points[index] = point4(0, start_height, distance_value, 1.0);
	ne = index;
	index++;
	points[index] = point4(distance_value, start_height, 0, 1.0);
	sw = index;
	index++;
	points[index] = point4(distance_value, start_height, distance_value, 1.0);
	se = index;
	index++;
	points_generated += 4;
	points_end += 4;
	xoffset++;

	amt_thr_pnts = 0;
	map[x][z] = gridSegment(points_start, points_end, x, z, nw, ne, sw, se, amt_thr_pnts, otherpoints);
	//map[x][z].print();

	for (int y = 0; y < grid_height; y++) {
		for (int i = 0; i < grid_width - 1; i++) {

			//start_height = 200 * sin(i);
			//small corrections need to make it form in a grid
			if (going_left) {
				i++;
				going_left = false;
			}
			else if (going_right) {
				i--;
				going_right = false;
			}
			points_start = index;
			points_end = index;
			if (go_right) {
				x++;
				xoffset_amount = xoffset * distance_value;
				zoffset_amount = zoffset * distance_value;
				nw = ne;
				sw = se;
				
				points[index] = point4(distance_value + xoffset_amount, start_height, 0 + zoffset_amount, 1.0);
				ne = index;
				index++;
				points[index] = point4(distance_value + xoffset_amount, start_height, distance_value + zoffset_amount, 1.0);
				se = index;
				index++;
				points_end += 4;
				points_generated += 2;
				xoffset++;
				
			}
			else {
				x--;
				xoffset -= 1;
				xoffset_amount = xoffset * distance_value;
				zoffset_amount = zoffset * distance_value;
				
				ne = nw;
				se = sw;
				points[index] = point4(0 + xoffset_amount, start_height, 0 + zoffset_amount, 1.0);
				nw = index;
				index++;
				points[index] = point4(0 + xoffset_amount, start_height, distance_value + zoffset_amount, 1.0);
				sw = index;
				index++;
				points_end += 4;
				points_generated += 2;
			}

			std::cout << x << "," << z << std::endl;
			if (x < grid_width) {
				map[x][z] = gridSegment(points_start, points_end, x, z, nw, ne, sw, se, amt_thr_pnts, otherpoints);
			}
		}
		z++;
		//check to makesure that it does not generate the start of the next row
		if (y != grid_height - 1) {
			if (go_right) {
				x = grid_height - 1;
				go_right = !go_right;
				going_left = true;
				//swapping to go the other way
				zoffset++;
				point4 temp = points[index - 3];
				zoffset_amount = zoffset * distance_value;
				points[index] = temp;
				index++;
				points[index] = point4(distance_value + xoffset_amount, start_height, distance_value + zoffset_amount, 1.0);
				index++;
				points[index] = temp;
				index++;
				points[index] = point4(0 + xoffset_amount, start_height, distance_value + zoffset_amount, 1.0);
				index++;

				points_generated += 4;
				//map[x][z] = gridSegment(points_start, points_end, x, z, nw, ne, sw, se, amt_thr_pnts, otherpoints);

		
				xoffset -= 2;
				xoffset_amount = xoffset * distance_value;
				zoffset_amount = zoffset * distance_value;

				points[index] = point4(0 + xoffset_amount, start_height, 0 + zoffset_amount, 1.0);
				index++;
				points[index] = point4(0 + xoffset_amount, start_height, distance_value + zoffset_amount, 1.0);
				index++;
				points_generated += 2;


				//map[x][z] = gridSegment(points_start, points_end, x, z, nw, ne, sw, se, amt_thr_pnts, otherpoints);

			}
			else {
				x = 1;
				go_right = !go_right;
				going_right = true;
				zoffset++;
				zoffset_amount = zoffset * distance_value;

				point4 temp = points[index - 3];
				points[index] = temp;
				index++;
				points[index] = point4(0 + xoffset_amount, start_height, distance_value + zoffset_amount, 1.0);
				index++;
				points[index] = point4(distance_value + xoffset_amount, start_height, distance_value + zoffset_amount, 1.0);
				index++;
				points[index] = temp;
				index++;
				points_generated += 4;

				//map[x][z] = gridSegment(points_start, points_end, x, z, nw, ne, sw, se, amt_thr_pnts, otherpoints);

			}
		}
	}
	mapDebug();

	raise_map_segment(5, 4, 4, 20);
}

//generates a recursive request to  raise the terrian 
void terrian1::raise_map_segment(int xloc, int yloc, int corn, int  amount) {

	std::vector<int*> r_value = map[xloc][yloc].raise(corn, amount, points);

	if (r_value.size() !=0) {
		for (int i = 0; i < r_value.size(); i++) {
			int n_xloc = r_value[i][0];
			int n_yloc = r_value[i][1];
			int n_corn = r_value[i][2];
			terrian1::map[n_xloc][n_yloc].raise(n_corn, amount, points);
			//delete[] r_value[i];//remove the allocated mem
		}
	}
}

void terrian1::mapDebug() {

	for (int y = 0; y < grid_height; y++) {
		for (int x = 0; x < grid_width; x++) {
			if (map[x][y].points_start == -1) {
				std::cout << " * ";
			}
			else {
				std::cout << " 1 ";
			}
		}
		std::cout << std::endl;
	}
}

//creates the data structure to manage all of the 
void terrian1::create_data_structure() {
	map = new gridSegment * [grid_width];
	for (int i = 0; i < grid_width; i++) {
		map[i] = new gridSegment[grid_height];
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