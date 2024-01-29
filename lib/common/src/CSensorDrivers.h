#pragma once

#include "globals.h"
#include "CSensorAdapter.h"

class CSensorDHT : public CSensorAdapter 
{
    public:
        CSensorDHT() {std::cout << "CSensorDHT 0-param constructor called" << std::endl;};
        CSensorDHT(SensorType inType = SensorType::DHT11S, unsigned char inPin = D4);
        virtual ~CSensorDHT() override;

        virtual SensorStatus getStatus() const override;
        virtual float readQuantity(std::vector<CQuantity>::const_iterator it) const;
        virtual void startSensing() override;

    private:
        std::unique_ptr<DHT> mSensorLibrary;
};
