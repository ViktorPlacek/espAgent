#include "globals.h"
#include "CAgent.h"
#include "CSensorAdapter.h"
#include <iterator>
#include <algorithm>

using namespace std;

void CAgent::parseConfiguration(void (*inFnc)(CAgent&))
{
	Log(DEBUG) << "CAgent::parseConfiguration from a global function called." << endl;
	inFnc(*this);

	Log(INFO) << "Parsed results:" << endl;
	Log(INFO) << "  Sensor: ";
	for (const auto& i : mSensors) {
		Log(INFO) << i->getType() << ": ";
		for (const auto& j : i->getQuantities()) {
			Log(INFO) << j.getName() << " (" << j.getType() << "), ";
		}
		Log(INFO) << endl;
	}

	Log(INFO) << "  Brokers: ";
	for (const auto& i : mBrokers) {
		Log(INFO) << i.getName() << "\t";
	}
	Log(INFO) << endl;

	Log(INFO) << "  Actuators:  ";
	for (const auto& i : mActuators) {
		Log(INFO) << i->getType() << ", ";
	}
	Log(INFO) << endl;

	Log(INFO) << "  Access Points:  ";
	for (const auto& i : mAccessPoints) {
	 	Log(INFO) << i.getSSID() << ", ";
	}
	Log(INFO) << endl;


}

void CAgent::addBroker(CBroker&& inBroker)
{
	Log(DEBUG) << "CAgent::addBroker(CBroker&&) called." << endl;

	mBrokers.push_back( move(inBroker) );
}

void CAgent::addSensor(SensorType inType, unsigned int inPin)
{
	Log(DEBUG) << "CAgent::addSensor called." << endl;

	switch (inType) {
		case SensorType::DHT11S :
		case SensorType::DHT12S :
		case SensorType::DHT21S :
		case SensorType::DHT22S :
			mSensors.emplace_back( unique_ptr<CSensorAdapter>( new CSensorDHT(inType, inPin) ) );
			Log(INFO) << inType << " sensor added to Agent sensors list." << endl;
			break;
		case SensorType::NONE :
			Log(INFO) << "No sensor added to Agent sensors list." << endl;
			break;
		default :
			Log(INFO) << "Unknown sensor type. Implement your sensor type in CAgent::parseConfiguration metod." << endl;
			break;
	}
}

void CAgent::addActuator(ActuatorType inType, unsigned int inPin)
{
	Log(DEBUG) << "CAgent::addActuator called." << endl;

	switch (inType) {
		case ActuatorType::RELAY :
			mActuators.emplace_back(new CActuatorRelay(inPin));
			Log(INFO) << "Actuator of type Relay was added." << endl;
			break;
		case ActuatorType::NONE :
			Log(INFO) << "No actuator added to Agent actuators list." << endl;
			break;
		default :
			Log(ERROR) << "Unknown actuator type. Implement your actuator type in CAgent::parseConfiguration method." << endl;
	}  
}

std::vector<CBroker>& CAgent::getBrokers()
{
	return mBrokers;
}

void CAgent::AccessPointConnect(list<CAccessPoint>::iterator inIt) 
// throws runtime exception when cannot connect to the access point.
{
	Log(DEBUG) << "CAgent::AccessPointConnect(" << inIt->getSSID() << ") called." << endl;
	inIt->connect();  // passing exception further
}

/**
 * @brief Scans for known access point and try to connect to it.
 * 
 * 	KNOWN_BUG: If it is not possible to connect to known access points (e.g. bad password), the algorithm fails to try other access points.
 * 
 * @return list<CAccessPoint>::iterator - iterator to the access point from the list of known access points that the device was connected to.
 */
list<CAccessPoint>::iterator CAgent::AccessPointConnect()
{
	Log(DEBUG) << "CAgent::AccessPointConnect() called" << endl;

	Log(DEBUG) << "Initiating AP scan." << endl;
	list<CAccessPoint> aps_found;  // using CAccessPoint class for temporary saving list of found access points

	// Scan for access points and save it to a temporary list
	int aps_found_count = WiFi.scanNetworks();
	if (aps_found_count == 0) {
		Log(ERROR) << "No access point found. Throwing exception." << endl;
		throw runtime_error("no one access point found in proximity.");
	}
	for (int i = 0; i < aps_found_count; ++i) {
		aps_found.emplace_back(WiFi.SSID(i).c_str(), ""); // watch out, new scan will discard c_str pointers!
		aps_found.back().setRSSI( WiFi.RSSI(i));
	}

	// Sort the list of found APs by RSSI descending
	aps_found.sort( [](const CAccessPoint& a, const CAccessPoint& b) {return a.getRSSI() < b.getRSSI();} );

	Log(DEBUG) << "Sorted found APs list: " << endl;
	for (const auto& it : aps_found) {
		Log(DEBUG) << "SSID: " << it.getSSID() << ", " << it.getRSSI() << endl;
	}

	// try to find if some of scanned access points is in the list of known access points
	auto known_ap = find_first_of(mAccessPoints.begin(), mAccessPoints.end(), aps_found.begin(), aps_found.end(),
			[](const CAccessPoint& a, const CAccessPoint& b) {return a.getSSID() == b.getSSID();} );

	if ( known_ap == mAccessPoints.end() ) {
		Log(ERROR) << "No known access point found." << endl;
		throw runtime_error("no known access point found.");
	}

	// Connect to found knwon AP
	try {
		AccessPointConnect(known_ap);
		Log(INFO) << "Successfully connected to SSID: " << known_ap->getSSID() << "." << endl;
		Log(INFO) << "Assigned IP address: " << WiFi.localIP().toString().c_str() << endl;
				Log(INFO) << mBrokers[0].getName() << "\t";

		return known_ap;
	} catch (const exception& e) {
		Log(DEBUG) << "CAgent::AccessPointConnect cautch exception: " << e.what() << "." << endl;
		Log(INFO) << "Access point SSID: " << known_ap->getSSID() << " timed out." << endl;
		throw runtime_error("Cannot connect to the Access Point.");
	}

	assert(false); // the program should never get here
}

void CAgent::BrokerConnect(std::vector<CBroker>::iterator inIt)
{
	Log(DEBUG) << "Connecting to broker " << inIt->getName() << "." << endl;

	try {
		inIt->connect();
	} catch(const exception& e) {
		Log(DEBUG) << "Cautch exception while calling CBroker::connect on broker: " << inIt->getName() << endl;
		Log(ERROR) << "Connection to broker " << inIt->getName() << " failed!" << endl;
		Log(ERROR) << "Error message: " << e.what() << endl;
	}
}

void CAgent::BrokerConnect()
{
	int count = 0;
	for (auto it = begin(mBrokers); it != end(mBrokers); ++it) {
		try {
			BrokerConnect(it);
			Log(INFO) << "Successfuly connected to broker " << it->getName() << "." << endl;
			++count;
		} catch (const exception& e) {
			Log(ERROR) << "Error when connecting to broker " << it->getName() << ": " << e.what() << "." << endl;
		}
	}
	mBrokersConnected += count;
}

void CAgent::BrokerDisconnect(std::vector<CBroker>::iterator inIt)
{
	Log(DEBUG) << "Disconnecting broker " << inIt->getName() << "." << endl;

	try {
		inIt->disconnect();
	} catch(const exception& e) {
		Log(DEBUG) << "Cautch exception while calling CBroker::disconnect on broker: " << inIt->getName() << endl;
		Log(ERROR) << "Disconnection of broker " << inIt->getName() << " failed!" << endl;
		Log(ERROR) << "Error message: " << e.what() << endl;
	}
}

void CAgent::BrokerDisconnect()
{
	int count = 0;
	for (auto it = begin(mBrokers); it != end(mBrokers); ++it) {
		try {
			BrokerDisconnect(it);
			Log(INFO) << "Successfuly disconnected from broker " << it->getName() << "." << endl;
			++count;
		} catch (const exception& e) {
			Log(ERROR) << "Error when disconnecting from broker " << it->getName() << " : " << e.what() << "." << endl;
		}
	}
	mBrokersConnected -= count;
}

vector<CQuantity> CAgent::SensorRead(std::vector< std::unique_ptr<CSensorAdapter> >::iterator inIt)
{
	Log(DEBUG) << "CAgent::SensorRead(" << (*inIt)->getType() << ") called." << endl;

	auto quantities = (*inIt)->getQuantities();
	vector<CQuantity> values;
	Log(DEBUG) << "Sensor has " << quantities.size() << " quantitites:" << endl;
	for (const auto& i : quantities) {
		Log(DEBUG) << "Quantity: " << i.getName() << endl;
	}

	for (auto qIt = begin(quantities); qIt != end(quantities); ++qIt) {
		try {
			qIt->setValue( (*inIt)->readQuantity(qIt) );
			values.push_back( *qIt );
			delay(2000);
		} catch (const exception& e) {
			Log(ERROR) << "CAgent::sensorRead failed: " << e.what() << endl;
		}
	}
	return values;
}

vector<CQuantity> CAgent::SensorRead()
{
	Log(DEBUG) << "CAgent::SensorRead called." << endl;
	vector<CQuantity> all_values;

	for (auto it = begin(mSensors); it != end(mSensors); ++it) {
		auto sensor_values = SensorRead(it);
		for (const auto& i : sensor_values) {
			all_values.push_back(i);
		}
	}
	return all_values;
}

void CAgent::SensorStartReading() 
{
	Log(DEBUG) << "CAgent::SensorStartReading called." << endl;

	for (auto it = begin(mSensors); it != end(mSensors); ++it) {
		SensorStartReading(it);
	}

}

void CAgent::SensorStartReading(std::vector< std::unique_ptr<CSensorAdapter> >::iterator inIt)
{
	Log(DEBUG) << "CAgent::SensorStartReading(" << (*inIt)->getType() <<") called." << endl;

	try {
		(*inIt)->startSensing();
	} catch (const exception& e) {
		Log(ERROR) << "CAgent::startSensing() failed: " << e.what() << endl;
	}
}


void CAgent::BrokerPublishSensor(std::vector< std::unique_ptr<CSensorAdapter> >::iterator inIt)
{
	Log(DEBUG) << "CAgent::BrokerPublishSensor(inIt) called." << endl;
	*inIt;
}

void CAgent::BrokerPublishSensor()
{
	Log(DEBUG) << "CAgent::BrokerPublishSensor called." << endl;
}

void CAgent::doSleep()
{
	Log(DEBUG) << "CAgent::doSleep called." << endl;

	switch (mSleepType){
		case SleepType::NONE :
			Log(WARN) << "None sleep set. Skipping doSleep command and continuing operation." << endl;
			break;

		case SleepType::LIGHT :
 			Log(DEBUG) << "Light sleep set. Modem is about to be disabled." << endl;
			Log(INFO) << "Going to bed. Waking again in " << mSleepDuration.count() << "ms." << endl;

			break;

		case SleepType::DEEP :
 			Log(DEBUG) << "Deep sleep set. Be sure to have Reset pin connected to Deep Sleep Timer pin otherwise the ESP is not going to wake up again until manually reset." << endl;
			Log(INFO) << "Going to bed. Waking again in " << mSleepDuration.count() << "ms." << endl;

			ESP.deepSleep(1000 * mSleepDuration.count());
			break;

		default:
			Log(ERROR) << "Sleep type not implemented! Skipping command and continuing operation." << endl;
		break;
	}
}