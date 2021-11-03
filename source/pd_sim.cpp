#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

struct vec3D {
	double x, y, z;
	vec3D( double x=0, double y=0, double z=0 ) 
		: x(x), y(y), z(z) {}

	friend std::ostream& operator
		<<(std::ostream& os, const vec3D& vec) {
			os << vec.x << " " << vec.y << " " << vec.z;
			return os;
		}
	
	double distance(vec3D v) {
		return std::sqrt(distance_sq(v));

	//use distance squared to avoid computing a root.  will just compare to delta*delta later
	double distance_sq(vec3D v) {
		return std::pow(x-v.x, 2) + std::pow(y-v.y, 2) + std::pow(z-v.z, 2);
	}

};

struct nbhd {
	std::vector<size_t> indicies;
	size_t v;
	nbhd(size_t v, std::vector<vec3D> pos, double delta) 
		: v(v)
	{
		find_indicies(pos, delta);
	}

	//optimize to check within delta*delta of each unit
	void find_indicies(std::vector<vec3D> pos, double delta) {
		delta *= 2;
		for(size_t k = 0; k < pos.size(); ++k) {
			if(pos[v].distance_sq(pos[k]) <= delta)
				indicies.push_back(k);
		}
	}
};

void meshGen( size_t lx, size_t ly, size_t lz, std::vector<vec3D>& pos ) {
	for( size_t x = 0; x < lx; ++x )
		for( size_t y = 0; y < ly; ++y )
			for( size_t z = 0; z < lz; ++z )
				pos.push_back(vec3D(x, y, z));
}

vec3D index_to_t0( size_t k , size_t lx, size_t ly, size_t lz ) {
	// k = ly * lz * x + y * lz + z
	vec3D v0();

	while ( k >= lz ) {
		while ( k >= lz * ly ) {
			++v.x;
			k -= lz * ly;
		}
		++v.y;
		k -= lz;
	}
	v.z += k;
	return v;
}

size_t t0_to_index( vec3D v, size_t lx, size_t ly, size_t lz ) {
	size_t k = v.x*ly*lz + v.y*lz + v.z;
	return k;
}

//stretch between xi and xj
double stretch( size_t i, size_t j, std::vector<vec3D> p, size_t lx, size_t ly, size_t lz ) {
	return ( p[i].distance(p[j]) - index_to_t0( i, lx, ly, lz ).distance(
				index_to_t0( j, lx, ly, lz )) ) /
			index_to_t0( i, lx, ly, lz ).distance( index_to_t0( j, lx, ly, lz ));	
}

//pair-wise force
vec3D pwForce( size_t i, size_t j, std::vector<vec3D> p, size_t lx, size_t ly, size_t lz, double c) {
	return c*stretch(i, j, p, lx, ly, lz)*(p[i] - p[j])/p[i].distance(p[j]);	
}

int main() {

	size_t lx, ly, lz, h;
	lx = ly = lz = 5;
	h = lx*ly*lz;

	std::vector<vec3D> positions;
	std::vector<double> volumes;
	std::vector<nbhd> nbhd_vec;

	meshGen(lx, ly, lz, positions);

	//read for file
	const size_t K = 160e9;
	const size_t Ki = 140e6;
	const size_t Phi = 8050;
	const size_t T = 1;
	const double dT = 1e-7;
	const double Delta = 3;

	for(size_t i = 0; i < positions.size(); ++i)
		neighborhoods.push_back( neighborhood(i, positions, Delta) );

	std::for_each(positions.begin(), positions.end(), 
			[](vec3D v) { std::cout << v << std::endl; });

	return 0;
}

