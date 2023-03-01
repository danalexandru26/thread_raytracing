#ifndef	BLOCK
#define BLOCK

#include<vector>
#include"../Vector/Vector.hpp"

using namespace math;

struct block
{
	block();
	block(int size);

	std::vector<vec3<float>> chunk;
};


#endif