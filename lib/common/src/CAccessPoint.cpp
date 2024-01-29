#include "CAccessPoint.h"

using namespace std;

/**
 * @brief Construct a new access point.
 * 
 */
CAccessPoint::CAccessPoint(std::string inSSID, std::string inPassword)
{
   Log(DEBUG) << "CAccessPoint constructor called with parameters inSSID: " << 
      inSSID <<", inPassword: " << inPassword << "." << endl; 

   mSSID = move(inSSID);
   mPassword = move(inPassword);
}

CAccessPoint::~CAccessPoint()
{
   Log(DEBUG) << "CAccessPoint destructor called." << endl;
}

/**
 * @brief Connects to an access point with specified SSID and password.
 * 
 * Throws runtime_error exception if connection was unsuccessful.
 * 
 */
void CAccessPoint::connect()
{
   Log(INFO) << "Connecting to SSID \"" << getSSID() << "\", password \"" << getPassword() << "\" ." << flush;
   Log(DEBUG) << "WiFi status before: " << WiFi.status() << endl;

	auto ssid_str = new char[mSSID.length() + 1]; // well, small memory leak
	strcpy(ssid_str, mSSID.c_str());
	auto password_str = new char[mPassword.length() + 1]; // well, small memory leak
	strcpy(password_str, mPassword.c_str());

	WiFi.begin( ssid_str,
					password_str );

	for (int i = 0; i < 8; ++i) {
		Log(INFO) << "." << flush;
		delay(1000);
		if (WiFi.status() == WL_CONNECTED) {
			Log(INFO) << "Sucessfuly connected to: " << getSSID() << "." << flush;
			Log(DEBUG) << "SSID: \"" << WiFi.SSID().c_str() << "\"." << endl;
			Log(DEBUG) << "RSSI: " << WiFi.RSSI() << "." << endl;
			return;
		}
	}
	Log(INFO) << endl;
	Log(DEBUG) << "Access point \"" << getSSID() << "\" timed out. Throwing exception." << endl;
	throw runtime_error("Access point connection time-out.");
}

/**
 * @brief Disconnect from an access point
 * 
 * No measures are made if disconnection was unsuccessful.
 * 
 */
void CAccessPoint::disconnect()
{
   Log(INFO) << "Disconnecting from SSID \"" << getSSID() << "\"." << flush;
   Log(DEBUG) << "WiFi status before: " << WiFi.status() << endl;

	if( WiFi.disconnect() ) {
      Log(INFO) << "Disconnected sucessfully." << endl;
   } else {
      Log(ERROR) << "Disconnection failed." << endl;
   }

}