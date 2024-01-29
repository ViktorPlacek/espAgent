#include "sconfigs.h"

using namespace std;

const std::array<struct WifiAp, 2> WifiApList {{
	{"espresso", "NoSugarPlease"},
	{"cappuccino", "WarmWithMilk"},
}};

void S1Config(CAgent& inAg)
{
	inAg.addSensor(SensorType::DHT11S, D4);

	inAg.addActuator(ActuatorType::NONE, D2);

	CBroker brk("Thingsboard Live Demo", "demo.thingsboard.io", 1883, 
					 "S1", "HsVuvSk3nLXYAGxxxxxx", "v1/devices/me/telemetry");
	inAg.addBroker( move(brk) );

	inAg.addBroker({"Thingsboard Cabin", "192.168.38.150", 1883, "S1", "HsVuvSk3nLXYAGU1LSww", "v1/devices/me/telemetry"});
	
	for (auto i : WifiApList) {
		inAg.mAccessPoints.emplace_back(i.Ssid, i.Password);
	}

	inAg.mBatteryType = BatteryType::LIPO;
	inAg.mSleepType = SleepType::DEEP;
	inAg.mSleepDuration = std::chrono::milliseconds(5 * 60 * 1000);
}

void S2Config(CAgent& inAg)
{
	inAg.addSensor(SensorType::DHT22S, D4);

	inAg.addActuator(ActuatorType::NONE);

	inAg.addBroker({"Thingsboard Live Demo", "demo.thingsboard.io", 1883, 
					 "S2", "O9oVxDeozVlz0mxxxxxx", "v1/devices/me/telemetry"});

	for (auto i : WifiApList) {
		inAg.mAccessPoints.emplace_back(i.Ssid, i.Password);
	}

	inAg.mBatteryType = BatteryType::LIPO;
	inAg.mSleepType = SleepType::DEEP;
	inAg.mSleepDuration = std::chrono::milliseconds(5 * 60 * 1000);
}

void S3Config(CAgent& inAg)
{
	inAg.addSensor(SensorType::DHT22S, D4);

	inAg.addActuator(ActuatorType::NONE);

	//inAg.addBroker( {"Thingsboard Live Demo", "demo.thingsboard.io", 1883, 
	//				 "S3", "wAV5KgV11v1SxQxxxxxx", "v1/devices/me/telemetry"} );
	CBroker brk("Thingsboard Home", "10.0.0.35", 1883, 
					"S3", "wAV5KgV11v1SxQxxxxxx", "v1/devices/me/telemetry");
	inAg.addBroker( move(brk) );

	for (auto i : WifiApList) {
		inAg.mAccessPoints.push_back({ i.Ssid, i.Password });
	}
	
	inAg.mBatteryType = BatteryType::LIPO;
	inAg.mSleepType = SleepType::DEEP;
	inAg.mSleepDuration = std::chrono::milliseconds(5 * 60 * 1000);
}

void S4Config(CAgent& inAg)
{
	inAg.addSensor(SensorType::DHT11S, D4);

	inAg.addActuator(ActuatorType::NONE);

	inAg.addBroker( {"Thingsboard Live Demo", "demo.thingsboard.io", 1883, 
					 "S4", "kgLoI4rsFeofb6xxxxxx", "v1/devices/me/telemetry"} );

	inAg.addBroker({"Thingsboard Cabin", "192.168.38.150", 1883, 
					"S4", "kgLoI4rsFeofb6xxxxxx", "v1/devices/me/telemetry"});

	for (auto i : WifiApList) {
		inAg.mAccessPoints.push_back({ i.Ssid, i.Password });
	}
	
	inAg.mBatteryType = BatteryType::LIPO;
	inAg.mSleepType = SleepType::DEEP;
	inAg.mSleepDuration = std::chrono::milliseconds(20 * 60 * 1000);
}

void S5Config(CAgent& inAg)
{
	inAg.addSensor(SensorType::DHT22S, D4);

	inAg.addActuator(ActuatorType::NONE);

	inAg.addBroker( {"Thingsboard Live Demo", "demo.thingsboard.io", 1883, 
					 "S5", "5EyxoUnx7cJIBYxxxxxx", "v1/devices/me/telemetry"} );

	inAg.addBroker({"Thingsboard Cabin", "192.168.38.150", 1883, 
					"S5", "5EyxoUnx7cJIBYxxxxxx", "v1/devices/me/telemetry"});

	for (auto i : WifiApList) {
		inAg.mAccessPoints.push_back({ i.Ssid, i.Password });
	}
	
	inAg.mBatteryType = BatteryType::LIPO;
	inAg.mSleepType = SleepType::DEEP;
	inAg.mSleepDuration = std::chrono::milliseconds(5 * 60 * 1000);
}

void S6Config(CAgent& inAg)
{
	inAg.addSensor(SensorType::DHT22S, D4);

	inAg.addActuator(ActuatorType::RELAY);

	inAg.addBroker( {"Thingsboard Live Demo", "demo.thingsboard.io", 1883, 
					 "S6", "LRkQh3aAGey8MLxxxxxx", "v1/devices/me/telemetry"} );

	inAg.addBroker({"Thingsboard Cabin", "192.168.38.150", 1883, 
					"S6", "LRkQh3aAGey8MLxxxxxx", "v1/devices/me/telemetry"});

	for (auto i : WifiApList) {
		inAg.mAccessPoints.push_back({ i.Ssid, i.Password });
	}
	
	inAg.mBatteryType = BatteryType::LIPO;
	inAg.mSleepType = SleepType::DEEP;
	inAg.mSleepDuration = std::chrono::milliseconds(5 * 60 * 1000);
}