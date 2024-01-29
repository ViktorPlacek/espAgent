#include <globals.h>
//#include "CSensorAdapter.h"

class CQuantity {
   public:
      CQuantity() = default;
      CQuantity(const MeasurementQuantity inType, const std::string& inName, const std::string& inUnit);
      CQuantity(const CQuantity&) = default;
      CQuantity(CQuantity&&) = default;
      CQuantity& operator=(CQuantity& rhs) = default;
      CQuantity& operator=(CQuantity&& rhs) = default;
      virtual ~CQuantity() = default;

      MeasurementQuantity getType() const;
      const std::string& getName() const;
      const std::string& getUnit() const;
      void setValue(float inValue);
      float getValue() const;

   private:
      MeasurementQuantity mType;
      std::string mName;
      std::string mUnit;
      float mValue;
};