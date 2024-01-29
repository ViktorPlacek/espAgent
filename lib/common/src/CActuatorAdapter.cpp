#include "CActuatorAdapter.h"

using namespace std;

CActuatorAdapter::CActuatorAdapter()
{
       Log << "CActuatorAdapter no-parameter constructor called." << std::endl;
}

CActuatorAdapter::~CActuatorAdapter()
{
       Log << "CActuatorAdapter destructor called." << std::endl;
}

ActuatorType CActuatorAdapter::getType() const
{
       return mType;
}
