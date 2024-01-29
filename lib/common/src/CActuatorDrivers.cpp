#include "CActuatorDrivers.h"

using namespace std;

CActuatorRelay::CActuatorRelay(unsigned char inPin)
{
   Log(DEBUG) << "CActuatorRelay constructor called. inPin: " << static_cast<int>(inPin) << "." << endl;
}

CActuatorRelay::~CActuatorRelay()
{
   Log(DEBUG) << "CActuatorRelay destructor called." << endl;
}



void CActuatorRelay::setON()
{
   Log(DEBUG) << "CActuatorRelay::setON() called." << endl;

   mState = true;
}

void CActuatorRelay::setOFF()
{
   Log(DEBUG) << "CActuatorRelay::setOFF() called." << endl;

   mState = false;

}

bool CActuatorRelay::getState() const
{
   Log(DEBUG) << "CActuatorRelay::getState() called." << endl;

   return mState;
}

void CActuatorRelay::setValue(float inValue)
{
   Log(DEBUG) << "CActuatorRelay::setValue() called. inValue: " << inValue << "." << endl;

   mValue = inValue;
}

int CActuatorRelay::getValue() const
{
   Log(DEBUG) << "CActuatorRelay::getValue() called." << endl;

   return mValue;
}
