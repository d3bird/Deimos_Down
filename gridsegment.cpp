#include "gridsegment.h"


gridSegment::gridSegment(int s, int e, int xl, int zl, int  nwl, int nel, int swl, int sel, int am_p, int* o) {
	points_start = s;
	points_end = e;
	x = xl;
	z = zl;
	nw = nwl;
	ne = nel;
	sw = swl;
	se = sel;
	amt_thr_pnts = am_p;
	otherpoints = o;
	inited = true;
}
gridSegment::gridSegment() {
	points_start = -1;
	points_end = -1;
	x = -1;
	z = -1;
	nw = -1;
	ne = -1;
	sw = -1;
	se = -1;
	amt_thr_pnts = -1;
	otherpoints = NULL;
	inited = false;
}
gridSegment::~gridSegment()
{
	delete otherpoints;
}

//debug print the cube info
void gridSegment::print() {
	std::cout << "range : " << points_start << " to " << points_end << std::endl;
	std::cout << "loc(x,z) : " << x << "," << z << std::endl;
	std::cout << "corners: " << nw << "," << ne << "," << sw << "," << se << std::endl;
	std::cout << amt_thr_pnts << " others points" << std::endl;
}

//rases the corners 
std::vector<int*> gridSegment::raise(int corn, int  amount, point4 *points) {
	std::vector<int*> output;
	if (inited) {
		int *data = new int[3];
		switch (corn)
		{
			//rase just a corneer up
		case 0:
			points[nw].y = amount;
			break;
		case 1:
			points[ne].y = amount;
			break;
		case 2:
			points[sw].y = amount;
			break;
		case 3:
			points[se].y = amount;
			break;
		case 4: // rases the whole square up
			points[nw].y = amount;
			points[ne].y = amount;
			points[sw].y = amount;
			points[se].y = amount;

			data[0] = x ;
			data[1] = z - 1;
			data[2] = 3;
			//std::cout << "exporting data: " << data[0] << " " << data[1]<<" "<< data[2] << std::endl;
			output.push_back(data);
			/*data = new int[3];
			data[0] = x;
			data[1] = z - 1;
			data[2] = 3;
			output.push_back(data);*/
			break;
		default:
			std::cout << corn << " : not a preprogrammed increment " << std::endl;
			std::cout << "inputed data: " << corn << " " << amount << std::endl;
			break;
		}
	}
	else {
		std::cout << "not inited" << std::endl;
	}
	return output;
}