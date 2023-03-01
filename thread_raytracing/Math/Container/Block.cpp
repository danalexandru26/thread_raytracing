#include"Block.hpp"

block::block() {
	chunk = std::vector < vec3<float>>();
}

block::block(int size) {
	chunk = std::vector<vec3<float>>(size);
}