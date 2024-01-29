#pragma once

#define DRYRUN

#include <Arduino.h>
#include <ESP8266WiFi.h> // 
#include <Adafruit_Sensor.h> // Adafruit Unified Sensor Library
#include <DHT.h> // DHT Sensor Library

#include <iostream>
#include <string>
#include <chrono>
#include <iostream>
#include <memory>
#include <list>
#include <limits>
#include <cassert>

#include "logger.h"

extern CLogger Log;

enum class SensorType : unsigned short
{
	 NONE,
	 DHT11S,
	 DHT12S,
	 DHT21S, // = AM2301
	 DHT22S // = AM2302
};

std::ostream& operator<< (std::ostream& ostr, const SensorType inType);

enum class MeasurementQuantity : unsigned short
{
	TEMPERATURE,
	HUMIDITY
};

std::ostream& operator<< (std::ostream& ostr, const MeasurementQuantity inQuant);

enum class SensorStatus : unsigned short
{
	 IDLE,
	 READING,
	 RESULT_READY
};

std::ostream& operator<< (std::ostream& ostr, const SensorStatus inStatus);

enum class ActuatorType :  unsigned short
{
	 NONE,
	 RELAY
};

std::ostream& operator<< (std::ostream& ostr, const ActuatorType inType);

enum class BatteryType : unsigned short
{
	 NONE,
	 LIPO
};

std::ostream& operator<< (std::ostream& ostr, const BatteryType inType);

enum class SleepType : unsigned short
{
	 NONE,
	 MODEM,
	 LIGHT,
	 DEEP
};

std::ostream& operator<< (std::ostream& ostr, const SleepType inType);

struct WifiAp
{
	 std::string Ssid;
	 std::string Password;
};

