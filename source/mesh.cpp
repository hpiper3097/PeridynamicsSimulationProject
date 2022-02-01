#include "mesh.h"

const double DELTA = 0.35;

Mesh::Mesh()
{
}

Mesh::Mesh(size_t parts)
{
    init(parts, true);
}

//fill _neighborhoodNest 'parts' cubed empty vectors.  parts references the number of pieces each dimension is split into
void Mesh::init( size_t parts, bool output )
{
    _parts = parts;
    _totalNodes = parts*parts*parts;
    for (size_t i = 0; i < _totalNodes; i++) {
        std::vector<size_t> tmp;
        _neighborhoodNest.push_back(tmp);
    }

    _generateNodes();
    _calculateNeighborhoods(DELTA);

    if(output)
    {
        std::cout << "nbhd size = " << _neighborhoodNest.size() << std::endl;
        std::cout << "node count = " << _totalNodes << std::endl;
        printNodes();
    }
}

void Mesh::_generateNodes()
{
    for(size_t cnt = 0; cnt < _totalNodes; cnt++)
    {
        Node tmpNode = Node(cnt, _parts);
        _nodes.push_back(tmpNode);
    }
}

void Mesh::_calculateNeighborhoods( double delta )
{
    std::for_each( _nodes.begin(), _nodes.end(), 
        [delta, this]( const Node fix )
        {
            std::for_each( _nodes.begin(), _nodes.end(), 
                [delta, fix, this]( const Node mov )
                {
                    if( distance( fix.pos(), mov.pos() ) <= delta )
                        _neighborhoodNest.at(fix.id()).push_back( mov.id() );
                }
            );
        }
    );
}

void Mesh::update()
{
    _updatePwForce();
    _updateAcceleration();
    _updateDisplacement();
    _updatePosition();
    _updateVolume();
}

void Mesh::_updatePwForce()
{

}

void Mesh::_updateAcceleration()
{

}

void Mesh::_updateDisplacement()
{

}

void Mesh::_updatePosition()
{

}

void Mesh::_updateVolume()
{

}

void Mesh::printNodes()
{
    std::for_each( _nodes.cbegin(), _nodes.cend(), 
        []( Node nod )
        {
            nod.printInfo();
        }
    );
}

//driver code
int main() {
    //..testing for 0 nodes, 1 node, 20 nodes, and 700 nodes

    Mesh cont(3);

    IO<size_t> io( "neighborhoods.csv" );
    io.write2DArrayToCSV( cont.neighborhoodNest() );

    std::getchar();

    return 0;
}