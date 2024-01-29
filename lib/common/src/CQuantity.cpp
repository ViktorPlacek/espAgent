#include <CQuantity.h>

using namespace std;

CQuantity::CQuantity(const MeasurementQuantity inType, const std::string& inName, const std::string& inUnit) :
   mType(inType), mName(inName), mUnit(inUnit)
{

}

MeasurementQuantity CQuantity::getType() const
{
   return mType;
}

const std::string& CQuantity::getName() const
{
   return mName;
}

const std::string& CQuantity::getUnit() const
{
   return mUnit;
}

void CQuantity::setValue(float inValue)
{
   if ( !isnan(inValue) ) {
      mValue = inValue;
   }
}

float CQuantity::getValue() const
{
   return mValue;
}