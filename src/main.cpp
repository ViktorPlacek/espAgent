#include <globals.h>
#include <sconfigs.h>
#include <CAgent.h>
#include <CSensorAdapter.h>
#include <CSensorDrivers.h>
#include <CBroker.h>
#include <CActuatorAdapter.h>
#include <CActuatorDrivers.h>

using namespace std;

CLogger Log(CLogger::DEBUG, false);
CAgent ag;

void setup()
{

	Serial.setDebugOutput(true);
	// necessary workaround to avoid automatic reconnecting to last known good access point
	WiFi.setAutoReconnect(false);
	WiFi.setAutoConnect(false);
	Serial.begin(115200);
	delay(300);

	cout << "Starting..." << endl;

	ag.parseConfiguration(S3Config); 

	ag.SensorStartReading();
	try {
		ag.AccessPointConnect();

		ag.BrokerConnect();
} catch (const exception& e) {
		Log(ERROR) << "Cannot connect to any broker: " << e.what() << " Aborting run." << endl;
		if (ag.mSleepType != SleepType::NONE) {
			ag.doSleep();
		} else {
			ag.mSleepType = SleepType::DEEP;
			ag.mSleepDuration = chrono::seconds(15 * 60);
			ag.doSleep();
		}
	}

	delay(2000);
	auto all_sensor_readings = ag.SensorRead();

	stringstream temp;
	temp << "{\"temperature\": " << all_sensor_readings[0].getValue() << ", \"humidity\": " << all_sensor_readings[1].getValue() << "}";

	for (auto &i : ag.getBrokers())
	{
		try
		{
			i.publish("v1/devices/me/telemetry", temp.str());
		}
		catch (const exception &e)
		{
			Log(ERROR) << e.what() << endl;
		}

		i.disconnect();
	}

	WiFi.disconnect();
	ag.doSleep();
}

void loop()
{

	cout << "Hello World!" << endl;

	WiFi.disconnect();
	delay(100);
	Log(INFO) << "Program finished. Idleing." << endl;

	while (true)
	{
		yield();
		cout << "." << flush;
		delay(2000);
	}
}

