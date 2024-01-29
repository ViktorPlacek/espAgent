#include "CSensorDrivers.h"

using namespace std;
using namespace std::chrono;

CSensorDHT::CSensorDHT(SensorType inType, unsigned char inPin)
{
    Log << "Call CSensorDHT constructor: inType : " << inType << ", inPin : " << static_cast<int>(inPin) << endl;
    
    switch (inType) {
        case SensorType::DHT11S :
            mSensorLibrary = unique_ptr<DHT>( new DHT(inPin, DHT11) );
            kReadCycleMin = duration<unsigned int, milli>(2000);
            break;

        case SensorType::DHT12S :
            mSensorLibrary = unique_ptr<DHT>( new DHT(inPin, DHT12) );
            kReadCycleMin = duration<unsigned int, milli>(2000);
            break;

        case SensorType::DHT21S :
            mSensorLibrary = unique_ptr<DHT>( new DHT(inPin, DHT21) );
            kReadCycleMin = duration<unsigned int, milli>(500);
            break;

        case SensorType::DHT22S :
            mSensorLibrary = unique_ptr<DHT>( new DHT(inPin, DHT22) );
            kReadCycleMin = duration<unsigned int, milli>(2000);
            break;

        case SensorType::NONE :
            kReadCycleMin = duration<unsigned int, milli>(100);
            Log(WARN) << "No any sensor defined." << endl;
            break;

        default :
            Log(ERROR) << "Sensor \"" << inType << "\"unknown to CSensorDHT class." << endl;
            kReadCycleMin = duration<unsigned int, milli>(100);
    }

    mQuantities.emplace_back(MeasurementQuantity::TEMPERATURE, "temperature", "\u00B0C");
    mQuantities.emplace_back(MeasurementQuantity::HUMIDITY, "humidity", "% RH");
    mSensorLibrary->begin();
    Log(DEBUG) << "Sensor " << inType << "initialzed successfully." << endl;

    mSensorType = inType;
    mPin = inPin;
    mSensorStatus = SensorStatus::IDLE;
    mTimeOfReadRequest = steady_clock::time_point::min();
}

CSensorDHT::~CSensorDHT() 
{
    Log(DEBUG) << "Call CSensorDHT destructor." << endl;
    switch (mSensorType) {
        case SensorType::DHT11S :
        case SensorType::DHT12S :
        case SensorType::DHT21S :        
        case SensorType::DHT22S :
            // Nothing to do.
            Log(INFO) << "DHT sensor deinitialized." << endl;
            break;
        default :
            break;
    }
}

SensorStatus CSensorDHT::getStatus() const
{
    Log << "CSensorDHT::getStatus() called." << endl;
    return(mSensorStatus);
}

float CSensorDHT::readQuantity(std::vector<CQuantity>::const_iterator it) const
{
    Log(DEBUG) << "CSensorDHT::readQuantity() called." << endl;
    Log(DEBUG) << "Quantity name: " << it->getName() << endl;

    if (mSensorStatus == SensorStatus::IDLE) {
        Log(INFO) << "CSensorDHT::getValue() called on Idle sensor. Throwing exception." << endl;
        throw runtime_error("reading not started. Call StartSensing first.");
    }

    if (mSensorStatus == SensorStatus::READING) {
        milliseconds read_request_elapsed = duration_cast<milliseconds>(steady_clock::now() - mTimeOfReadRequest);
        Log << "Time from the read request: " << read_request_elapsed.count() << "ms" << endl;
        if (read_request_elapsed < kReadCycleMin) {
            Log(INFO) << "CSensorDHT::getValue() called on sensor with unprepared result. Throwing exception." << endl;            
            throw runtime_error("result is not ready. Sensor is still reading.");
        } else {
            mSensorStatus = SensorStatus::RESULT_READY;
        }
    }

    float result;
    if (mSensorStatus == SensorStatus::RESULT_READY) {
        switch (mSensorType) {
            case SensorType::DHT11S :
            case SensorType::DHT12S :
            case SensorType::DHT21S :
            case SensorType::DHT22S :
                switch( it->getType() ) {
                    case MeasurementQuantity::TEMPERATURE :
                        Log(DEBUG) << "Calling DHT.readTemperature." << endl;
                        result = mSensorLibrary->readTemperature(false, false);
                        break;
                    case MeasurementQuantity::HUMIDITY :
                        Log(DEBUG) << "Calling DHT.readHumidity." << endl;
                        result = mSensorLibrary->readHumidity(false);
                        break;
                    default :
                        Log(ERROR) << "Unknown quantity for DHT sensor: " << it->getName() << endl;
                        stringstream temp;
                        temp << "DHT sensor cannor read quantity \"" << it->getName() << "\".";
                        throw runtime_error( temp.str() );
                }
                break;
            default :
                Log(ERROR) << "Unknown sensor type. Implement your sensor to CSensorDrivers.h first." << endl;
                stringstream temp;
                temp << "Unknown sensor type: \"" << mSensorType << "\".";
                throw runtime_error( temp.str() );
        }

        if ( isnan(result) ) {
            throw runtime_error("sensor read value was NaN.");
        }
        Log(DEBUG) << "CSensorDHT::readValue() result : \"" << it->getName() << " = " <<
             result << " " << it->getUnit() << "\"." << endl;
        return result;
    }
    assert(false); // program should never enter here
}

void CSensorDHT::startSensing() 
{
    Log << "CSensorDHT::StartSensing() called." << endl; 
    if (mSensorStatus == SensorStatus::READING) {
        milliseconds read_request_elapsed = duration_cast<milliseconds>(steady_clock::now() - mTimeOfReadRequest);
        Log << "Time from the read request: " << read_request_elapsed.count() << "ms" << endl;
        if (read_request_elapsed < kReadCycleMin) {
            throw runtime_error("Sensor is already sensing.");
        } else {
            mSensorStatus = SensorStatus::RESULT_READY;
        }
    }

    // Nothing to do for DHT
    // Restart reading even if the result is already prepared.
    Log(DEBUG) << "Start reading of sensor data." << endl;
    mTimeOfReadRequest = steady_clock::now();
    mSensorStatus = SensorStatus::READING;
}
