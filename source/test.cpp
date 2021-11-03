#include "mesh.h"
#include <iostream>

int main()
{
	Mesh m = Mesh(25);

	std::cout << 25*25*25 << " points in configuration:\n";
	for( size_t i = 0; i < 25*25*25; ++i )
		std::cout << m.pos(i) << std::endl;

	return 0;
}
