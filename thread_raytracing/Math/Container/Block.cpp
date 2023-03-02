#include"Block.hpp"

block::block() {
	chunk = std::vector < vec3<double>>();
}

block::block(int size) {
	chunk = std::vector<vec3<double>>(size);
}