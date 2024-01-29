#include <unity.h>
#include <iostream>
#include <string>
#include <vector>

#include <globals.h>
#include <CAgent.h>
#include <CSensorAdapter.h>
#include <CSensorDrivers.h>
#include <CBroker.h>
#include <CActuatorAdapter.h>
#include <CActuatorDrivers.h>


using namespace std;

CLogger Log(CLogger::DEBUG, false);

 void setup() {
	cout << "Hello." << endl;
	DeviceConfig dconf;
	S1Config(dconf);

	CAgent ag;
	ag.parseConfiguration(dconf);

	for (const auto& i : ag.getBrokers()) {
		cout << i.getID() << "\t";
	}
	cout << endl;
}

void loop() {
	 // put your main code here, to run repeatedly:
}

int main()
{
   UNITY_BEGIN();

	setup();

	loop();

   UNITY_END();
}
