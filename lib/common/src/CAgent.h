#pragma once
#include "globals.h"
#include "CBroker.h"
#include "CAccessPoint.h"
#include "CSensorAdapter.h"
#include "CSensorDrivers.h"
#include "CActuatorAdapter.h"
#include "CActuatorDrivers.h"

class CAgent 
{
    public:
        CAgent() = default;
        CAgent(const CAgent& rhs) = delete;
        CAgent& operator= (const CAgent& rhs) = delete;
        virtual ~CAgent() = default;

        virtual void parseConfiguration(void (*inFnc)(CAgent&));
        virtual void addBroker(CBroker&& inBroker);
        virtual void addSensor(SensorType inType, unsigned int inPin = D4);
        virtual void addActuator(ActuatorType inType, unsigned int inPin = D4);
        virtual std::vector<CBroker>& getBrokers();
        virtual std::list<CAccessPoint>::iterator AccessPointConnect(); 
        virtual void AccessPointConnect(std::list<CAccessPoint>::iterator inIt);
        virtual void BrokerConnect(std::vector<CBroker>::iterator inIt);
        virtual void BrokerConnect();
        virtual void BrokerDisconnect(std::vector<CBroker>::iterator inIt);
        virtual void BrokerDisconnect();
        virtual std::vector<CQuantity> SensorRead(std::vector< std::unique_ptr<CSensorAdapter> >::iterator inIt);
        virtual std::vector<CQuantity> SensorRead();
        virtual void SensorStartReading();
        virtual void SensorStartReading(std::vector< std::unique_ptr<CSensorAdapter> >::iterator inIt);
        virtual void BrokerPublishSensor(std::vector< std::unique_ptr<CSensorAdapter> >::iterator inIt);
        virtual void BrokerPublishSensor();
        virtual void doSleep();

    public:
        std::vector< std::unique_ptr<CSensorAdapter> > mSensors;
        std::vector<CBroker> mBrokers;
        std::vector< std::unique_ptr<CActuatorAdapter> > mActuators;
        std::list<CAccessPoint> mAccessPoints;
        BatteryType mBatteryType;
        SleepType mSleepType;
        std::chrono::milliseconds mSleepDuration = std::chrono::milliseconds(1000);

        int mBrokersConnected = 0;
};