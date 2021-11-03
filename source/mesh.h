#pragma once
#include <vector>
#include <iostream>
#include <cmath>

#include "parser.h"

#define BEEEG 500

struct vec3D
{
	double x, y, z;
	vec3D( double x=0, double y=0, double z=0 );
	
	vec3D operator +( const vec3D rhs );
	vec3D operator -( const vec3D rhs );
	vec3D operator *( const double r );
	vec3D operator /( const double r );
};

std::ostream& operator<<( std::ostream& os, const vec3D& vec );

double distanceSq( vec3D u, vec3D v );
double distance( vec3D u, vec3D v );

class Mesh
{
	private:
		std::vector<vec3D> _positions;
		std::vector<double> _volumes;
		size_t _lx, _ly, _lz;
		double _c, _sc;
		Parser _p;

		void _init();
		size_t _mu( size_t i, size_t j);

	public:
		Mesh();		//for lx = ly = lz = BEEEG
		Mesh( size_t alt_sz);		//testing smaller mesh side lengths

		void gen();	//called in constructor

		vec3D pos( size_t k );	//return vec from positions
		void wpos( size_t k, vec3D v );	//write v to positions[k]

		vec3D indexToX0( size_t k );	//takes an index k and returns that vec3D at t = 0

		double stretch( size_t i, size_t j );		//stretch between xi and xj at time t
		vec3D pwForce( size_t i, size_t j);	//pair-wise force between xi and xj at time t
};

