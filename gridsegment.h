#pragma once

#include <iostream>
#include <glew.h>
#include <freeglut.h>
#include "angel/Angel.h"

typedef Angel::vec4  point4;

//the return type of the raise function to tell the terrian
//that other grid segments need to be updated
struct need_update {
	need_update() {}
	
};

class gridSegment {
public:

	gridSegment(int s, int e, int xl, int zl, int  nwl, int nel, int swl, int sel, int am_p, int* o);
	gridSegment();
	~gridSegment();

	void print();
	//raises the points in a square then returns a vec3 
	need_update* raise(int corn, int  amount, point4* points);


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
