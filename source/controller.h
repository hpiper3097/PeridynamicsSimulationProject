#pragma once
#include "mesh.h"

class Controller
{
    private:
        double _deltaTime, _time, _maxTime;
        size_t _timeStep;
        Mesh _mesh;
        //size_t threads;
    public:
        Controller();
        bool init();
        void evaluate();
};