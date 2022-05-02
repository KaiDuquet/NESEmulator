#include <iostream>
#include <cstdlib>

int main() {
	uint8_t* ram = (uint8_t*)calloc(64 * 1024, sizeof(uint8_t));
	if (!ram) return 1;
	std::cout << ram << " " << ram + 1;
	free(ram);
	return 0;
}