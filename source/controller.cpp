#include "controller.h"

Controller::Controller()
{

}

bool Controller::init()
{
    _deltaTime = .1;
    _time = 0.f;
    _timeStep = 0;
    _maxTime = 2.5f;
    return true;
}

void Controller::evaluate()
{
    while( _time < _maxTime )
    {
        // compute pairwise force f
        // add external force b
        // compute acceleration a
        // compute displacement mu
        // update positions

        _timeStep++;
        _time = _deltaTime * _timeStep;
    }
}