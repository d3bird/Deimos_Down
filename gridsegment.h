#pragma once

#include <iostream>
#include <glew.h>
#include <freeglut.h>
#include "angel/Angel.h"
#include <String>
#include <vector>

typedef Angel::vec4  point4;

class gridSegment {
public:

	gridSegment(int s, int e, int xl, int zl, int  nwl, int nel, int swl, int sel, int am_p, int* o);
	gridSegment();
	~gridSegment();

	void print();
	//raises the points in a square then returns a vec3 
	std::vector<int*>  raise(int corn, int  amount, point4* points);

	bool inited;
	//the range of the points
	int points_start;
private:
	int points_end;
	//location in the world, should corispond to the location in the data struct
	int x, z;
	//corrners 
	int nw, ne, sw, se;
	//if there are any other points in the square
	int amt_thr_pnts;
	int* otherpoints;
};
