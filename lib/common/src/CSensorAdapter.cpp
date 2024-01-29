#include "CSensorAdapter.h"

using namespace std;

CSensorAdapter::CSensorAdapter() 
{
    Log << "CSensorAdapter no-parameter constructor called." << endl;
}

CSensorAdapter::~CSensorAdapter()
{
    Log << "CSensorAdapter destructor called." << endl;
}

SensorType CSensorAdapter::getType() const
{
    return mSensorType;
}

unsigned char CSensorAdapter::getPin() const
{
    return mPin;
}

const std::vector<CQuantity>& CSensorAdapter::getQuantities() const
{
    return mQuantities;
}

void CSensorAdapter::addQuantity(MeasurementQuantity inQuantity, const string& inName, const string& inUnit)
{
    Log(DEBUG) << "CSensorAdapter::addQuantity() called." << endl;
    mQuantities.emplace_back(inQuantity, inName, inUnit);
}
