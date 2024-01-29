# ESP Agent

	ESP8266 firmware for sensor data acquisition and reporting periodically using MQTT. 
	Although I sucessfully use 5 sensors with this firmware it is still a half-made product 
	intended for fellow c++ developer (althogh a begginer) to extend.
	
## Features

 - static (hard-wired) configuration in separate source file
 - scan proximity WiFi hot spots and try to connect to configured one
 - reads data from configured sensors
 - try to connect to configured MQTT brokers
 - sends data from sensors to brokers
 - go to one of configured sleeps for configured duration
 - rich logging through serial port
 
## Planned Features (just a vision, no date estimation)

 - reading configuration from a file
 - uploading configuration via FTP
 - fallback to just FTP functionality if config failes (fallback config file?)
 - logging into files with a sequence number
 - decorators for measurement values conditioning (filters, statistics, corrections etc.)
 - implement static_assert checks of class enums
 - change architecture to CBroker->vector of CQuantity each with a reference to its CSensor
 - measure battery voltage (capacity?) using one of imputs

## Platform

 - Uses PlatformIO framework in Visual Studio Code
- Writen in C++ v11
- Currently tested only against D1 Mini ESP8266 module
- Uses Arduino libraries