#include "mesh.h"

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
	return (r != 0) ? vec3D(x/r, y/r, z/r) : vec3D();
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

Mesh::Mesh()
{
	_lx = _ly = _lz = BEEEG;
	_init();
	gen();
	_fillNbhd( _lx*_ly*_lz );
}

Mesh::Mesh( size_t alt_sz )
{
	_lx = _ly = _lz = alt_sz;
	_init();
	gen();
	_fillNbhdOutput( _lx*_ly*_lz );
}

void Mesh::_init()
{
	_p = Parser();
	_delta = _p.delta();
	_c = 18*_p.K()/_p.delta()/M_PI;
	_sc = 5/12* std::sqrt(
			_p.Kic() / ( _p.K()*_p.K()*_p.delta() ) );
}

void Mesh::gen()
{
	for ( size_t x = 0; x < _lx; ++x )
		for ( size_t y = 0; y < _ly; ++y )
			for ( size_t z = 0; z < _lz; ++z )
				_positions.push_back( vec3D(x, y, z) );
}

void Mesh::_fillNbhd( size_t k )
{
	size_t a, b, c, j;
	vec3D v = vec3D();
	for ( size_t i = 0; i < k; ++i ) {
		v = _positions[i];
		for ( a = _delta; a >= 0 && a <= _delta; a-- ) {
			for ( b = 0; b <= _delta - a; ++b ) {
				for ( c = 0; c <= _delta - a - b; ++c ) {
					if ((v.x+a < _lx) && (v.y+b < _ly) && (v.z+c < _lz)) 
						//don't touch anything outside our bounds
					{
						j = (v.x + a) * _ly * _lz
								+ (v.y + b) * _lz
								+ (v.z + c);
						_positions[i].nbhd.push_back(j);	
						_positions[j].nbhd.push_back(i);
					}
				}
			}
		}	
	}
}

bool Mesh::_distanceAssertLessThanDelta( vec3D u, vec3D v )
{
	return  (distance(u, v) <= _delta);
}

void Mesh::_fillNbhdOutput( size_t k )
{
	size_t a, b, c, j;
	vec3D v = vec3D();
	for ( size_t i = 0; i < _positions.size(); ++i ) {
		std::cout << i << ":\n";
		v = _positions[i];
		for ( a = _delta; a >= 0 && a <= _delta; a-- ) {
			for ( b = 0; b <= _delta - a; ++b ) {
				for ( c = 0; c <= _delta - a - b; ++c ) {
					if ((v.x+a < _lx) && (v.y+b < _ly) && (v.z+c < _lz))
					{
						j = (v.x + a) * _ly * _lz
								+ (v.y + b) * _lz
								+ (v.z + c);
						if(i != j )//&& _distanceAssertLessThanDelta( v, _positions[j]))
						{
							std::cout << "\t" << j << ":\n";
							_positions[i].nbhd.push_back(j);	
							_positions[j].nbhd.push_back(i);
							std::cout << "\t" <<
								_positions[i] << " affects "
								<< _positions[j] << ".\n";
						}
					}
				}
			}
		}	
	}
}

void Mesh::_fillNbhdOutputOld( bool output )
{
	for ( size_t k = 0; k < _positions.size(); ++k ) {
		if( output )
			std::cout << k << ":\n";
		for ( size_t l = 0; l < _positions.size(); ++l ) {
			if ( distanceSq( _positions[k], _positions[l] ) < _delta*_delta ) {
				_positions[k].nbhd.push_back(l);
				if( output )
					std::cout << "\t" <<
						_positions[k] << " to " << _positions[l]
						<< " < " << _delta << ".\n";
			}
		}
	}
}

vec3D Mesh::pos( size_t k )
{
	return _positions[k];
}

void Mesh::wpos( size_t k, vec3D v )
{
	_positions[k] = v;
}

vec3D Mesh::indexToX0( size_t k )
{
	// k = x * _ly * _lz + y * _lz + z
	vec3D v0 = vec3D();

	while ( k >= _lz )
	{
		while ( k >= _lz * _ly )
		{
			++(v0.x);
			k -= _lz * _ly;
		}
		++(v0.y);
		k -= _lz;
	}
	(v0.x) += k;
	return v0;
}

double Mesh::stretch( size_t i, size_t j )
{
	return (distance(pos(j), pos(i)) - distance(indexToX0(j), indexToX0(i))) / 
		distance(indexToX0(j), indexToX0(i));
}

size_t Mesh::_mu( size_t i, size_t j)
{
	return (stretch(i, j) < _sc) ? 1 : 0;
}

vec3D Mesh::pwForce( size_t i, size_t j)
{
	return (pos(j) - pos(i)) / distance(pos(j), pos(i)) * stretch(i, j) * _mu(i, j) * _c ;
}

vec3D Mesh::_netForce( size_t i )
{
	vec3D net = vec3D();

	//need to iterate through neighborhood
	
	return net;
}

void Mesh::netForce()
{
	size_t i = 0;
	while ( i < _lx*_ly*_lz )	
		_netForce(i++);
}



