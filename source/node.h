#pragma once
#include <iostream>

/*
*	@brief Representation of 3D vector
*/
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

/*
*	@brief The 'atom' of the PD simulation 
*****************************************************************************/
class Node
{
	private:
	vec3D _pos;
	size_t _id;

	public:
	/*
	*	@brief Initialize all to 0's	
	*****************************************************************************/
	Node() : _pos(vec3D(0, 0, 0)), _id(0) {};
	/*
	*	@brief Initialize _id with _pos to 0's
	*****************************************************************************/
	Node( size_t id ) : _id(id), _pos( vec3D(0, 0, 0) ) {};
	/*
	*	@brief Initialize _id and _pos directly
	*/
	Node( size_t id, vec3D pos) : _id(id), _pos(pos) {};
	/*
	*	@brief Initialize _id and construct _pos from parts
	*	@params parts Refers to the number of partitions of each unit axis.  W
	***************************************************************************/
	Node( size_t id, size_t parts );

	inline const size_t id() const { return _id; }
	inline const vec3D pos() const { return _pos; }

// ... debug..
	void printInfo();
};

/*
*	Utility functions
*/
double distanceSq( vec3D u, vec3D v );
double distance( vec3D u, vec3D v );
vec3D nodeIDtoStartPos( size_t id, size_t parts );