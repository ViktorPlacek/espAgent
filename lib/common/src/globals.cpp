#include "globals.h"
#include "CAgent.h"
//#include "CSensorDHT.h"

using namespace std;

std::ostream& operator<< (std::ostream& ostr, const SensorType inType)
{
	static const vector<string> TypeStrings = {"none",  "DHT11",
                                                        "DHT12",
                                                        "DHT21",
                                                        "DHT22"};

    if (static_cast<int>(inType) <= static_cast<int>( TypeStrings.size() )) {
	    ostr << TypeStrings[static_cast<size_t>(inType)];
    } else {
        ostr << "<undefined sensor type>";
        Log(WARN) << "Used sensor type is not defined in operator<< TypeStrings const array for SensorType." << endl;
    }
    return(ostr);
}

std::ostream& operator<< (std::ostream& ostr, const MeasurementQuantity inQuant)
{
	static const vector<string> QuantityStrings = {"temperature",  "humidity"};

    if (static_cast<int>(inQuant) <= static_cast<int>( QuantityStrings.size() )) {
	    ostr << QuantityStrings[static_cast<size_t>(inQuant)];
    } else {
        ostr << "<undefined sensor type>";
        Log(WARN) << "Used sensor type is not defined in operator<< TypeStrings const array for SensorType." << endl;
    }
    return(ostr);
}

std::ostream& operator<< (std::ostream& ostr, const SensorStatus& inStatus)
{
	static const vector<string> StatusStrings = {"idle", "reading", "result ready"};

    if (static_cast<int>(inStatus) <= static_cast<int>( StatusStrings.size() )) {
	    ostr << StatusStrings[static_cast<size_t>(inStatus)];
    } else {
        ostr << "<undefined status type>";
        Log(WARN) << "Used status type is not defined in operator<< StatusStrings const array for StatusType." << endl;
    }
    return(ostr);
}

std::ostream& operator<< (std::ostream& ostr, const ActuatorType inType)
{
    cout << "Before before." << endl;
	static const vector<string> TypeStrings = {"none", "relay"};

    if (static_cast<int>(inType) <= static_cast<int>( TypeStrings.size() )) {
        Log(DEBUG) << "before" << endl;
	    ostr << TypeStrings[static_cast<unsigned short>(inType)];
        Log(DEBUG) << "afrer" << endl;
    } else {
        ostr << "<undefined actuator type>";
        Log(WARN) << "Used actuator type is not defined in operator<< StatusStrings const array for ActuatorType." << endl;
    }
    return(ostr);

}

std::ostream& operator<< (std::ostream& ostr, const BatteryType inType)
{
	static const vector<string> BatteryStrings = {"none", "LIPO"};

    if (static_cast<int>(inType) <= static_cast<int>( BatteryStrings.size() )) {
	    ostr << BatteryStrings[static_cast<size_t>(inType)];
    } else {
        ostr << "<undefined battery type>";
        Log(WARN) << "Used battery type is not defined in operator<< BatteryStrings const array for BatteryType." << endl;
    }
    return(ostr);
}

std::ostream& operator<< (std::ostream& ostr, const SleepType inType)
{
	static const vector<string> SleepStrings = {"none", "LIPO"};

    if (static_cast<int>(inType) <= static_cast<int>( SleepStrings.size() )) {
	    ostr << SleepStrings[static_cast<size_t>(inType)];
    } else {
        ostr << "<undefined sleep type>";
        Log(WARN) << "Used sleep type is not defined in operator<< SleepStrings const array for SleepType." << endl;
    }
    return(ostr);
}

