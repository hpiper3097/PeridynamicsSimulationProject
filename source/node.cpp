#include "node.h"

vec3D::vec3D( double x, double y, double z )
	: x(x), y(y), z(z) {}

vec3D vec3D::operator +( const vec3D rhs )
{
	return vec3D(x+rhs.x, y+rhs.y, z+rhs.z);
}

vec3D vec3D::operator -( const vec3D rhs )
{
	return vec3D(x-rhs.x, y-rhs.y, z-rhs.z);
}

vec3D vec3D::operator *( const double r )
{
	return vec3D(r*x, r*y, r*z);
}

vec3D vec3D::operator /( const double r )
{
	if(r != 0)
		return vec3D(x/r, y/r, z/r);
	return vec3D();
}

std::ostream& operator<<( std::ostream& os, const vec3D& vec )
{
	return os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
}

double distanceSq( vec3D u, vec3D v )
{
	return std::pow(u.x - v.x, 2) + std::pow(u.y - v.y, 2) + std::pow(u.z - v.z, 2);
}

double distance( vec3D u, vec3D v )
{
	return std::sqrt( distanceSq(u, v) );
}

//computue starting positions with partitions along each dimension and ID nums given 3 dimensions
vec3D nodeIDtoStartPos( size_t ID, size_t parts )
{
	size_t rem = 0;
	double x1, x2, x3;
	x1 = x2 = x3 = 0.f;

	//INTEGER DIVISION!!! 63 / 12 = 3 here!!!
	x1 = ID / (parts*parts);
	rem = ID % (parts*parts);
	//INTEGER DIVISION AGAIN!!!
	x2 = rem / parts;
	rem = rem % parts;
	x3 = rem;

	//divide by parts so that we work on unit cube
	x1 /= parts;
	x2 /= parts;
	x3 /= parts;

	//finally, center the positions with respect to the volumes they represent
	x1 += 1.f/(2*parts);
	x2 += 1.f/(2*parts);
	x3 += 1.f/(2*parts);

	return vec3D(x1, x2, x3);
}

Node::Node( size_t id, size_t parts )
	:	_id(id)
{
	_pos = nodeIDtoStartPos( id, parts );	
}

void Node::printInfo()
{
	std::cout << "Node ID:\t" << _id << std::endl;
	std::cout << "Node Position:\t" << _pos << std::endl;
}