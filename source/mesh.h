#pragma once
#include "node.h"
#include "io.h"
#include <vector>
#include <algorithm>

/*
*   @class Mesh
*   @brief The material composed of multiple nodes.
***************************************************************************/
class Mesh {
    private:
        size_t _parts, _totalNodes;
        std::vector<vec3D> _positions, _pwForces, _accelerations, _displacements;
        std::vector<double> _volumes;
        std::vector<std::vector<size_t>> _neighborhoodNest;

        void _generateNodes();
        void _calculateNeighborhoods( double delta );

        void _updatePwForce();
        void _updateAcceleration();
        void _updateDisplacement();
        void _updatePosition();
        void _updateVolume();

    public:
        Mesh();
        Mesh( size_t parts );

        //make private and potentially change type for better output
        std::vector<Node> _nodes;

        void init( size_t parts, bool output=false ); //for gen nodes and nbhd calc
        void update();  //update vectors for position, volume [, p-w force, acceleration, displacement]

        void printNodes();
        void clear();
        void tmpFuncJoin( size_t nodes );

        inline const std::vector<std::vector<size_t>> neighborhoodNest() const { return _neighborhoodNest; }
};