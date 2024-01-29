#pragma once
#include "globals.h"
#include "CQuantity.h"

class CSensorAdapter {
    public:
        CSensorAdapter();
        CSensorAdapter(const CSensorAdapter& rhs) = delete;
        CSensorAdapter(CSensorAdapter&& rhs) = default;
        CSensorAdapter& operator= (const CSensorAdapter& rhs) = delete;
        CSensorAdapter& operator= (CSensorAdapter&& rhs) = default;
        virtual ~CSensorAdapter();

        virtual SensorType getType() const;
        virtual unsigned char getPin() const;
        virtual const std::vector<CQuantity>& getQuantities() const;
        virtual void addQuantity(MeasurementQuantity inQuantity, const std::string& inName, const std::string& inUnit);
        virtual SensorStatus getStatus() const = 0;
        virtual float readQuantity(std::vector<CQuantity>::const_iterator it) const = 0;
        virtual void startSensing() = 0;
        
    
    protected:
        SensorType mSensorType;
        unsigned char mPin;
        mutable SensorStatus mSensorStatus;
        std::vector<CQuantity> mQuantities;
        mutable float mLastReading;
        std::chrono::milliseconds kReadCycleMin;
        std::chrono::steady_clock::time_point mTimeOfReadRequest;
};

