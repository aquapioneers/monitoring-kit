#pragma once


// Include the necessary libraries for the auxiliary sensor to be used
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "Adafruit_SHT31.h"
#include <MCP3424.h>

#include <Sensors.h>
#include <DS2482.h>

class AuxBoards {
public:
	void setup();
	float getReading(SensorType wichSensor);

private:
};

class AlphaDelta {
public:

	struct Resistor {
		byte deviceAddress;
		byte resistorAddress;
	};

	bool begin();

	// SHT31 Temperature and Humidity Sensor
	Adafruit_SHT31 sht31 = Adafruit_SHT31();
	float getTemperature();
	float getHumidity();

	// Alphasense Gas Sensors
	enum Electrodes {AE_1, WE_1, AE_2, WE_2, AE_3, WE_3};
	double getElectrode(Electrodes wichElectrode);

	// Alphasense Digital Potenciometers
	Resistor POT_AE1 = {0x55, 0x01};
	Resistor POT_WE1 = {0x55, 0x00};
	Resistor POT_AE2 = {0x56, 0x01};
	Resistor POT_WE2 = {0x56, 0x00};
	Resistor POT_AE3 = {0x54, 0x01};
	Resistor POT_WE3 = {0x54, 0x00};

	void setPot(Resistor wichPot, uint32_t value);
	uint32_t getPot(Resistor wichPot);
	const float ohmsPerStep = 392.1568;     // Resistor conversion constant in Ohms. (100,000 / 255)

private:
};

class GrooveI2C_ADC {
public:

	bool begin();
	float getReading();

	const byte deviceAddress 	= 0x59;
	const float V_REF 			= 3.30;
	const byte REG_ADDR_RESULT	= 0x00;
	const byte REG_ADDR_ALERT	= 0x01;
	const byte REG_ADDR_CONFIG	= 0x02;
	const byte REG_ADDR_LIMITL	= 0x03;
	const byte REG_ADDR_LIMITH	= 0x04;
	const byte REG_ADDR_HYST	= 0x05;
	const byte REG_ADDR_CONVL	= 0x06;
	const byte REG_ADDR_CONVH	= 0x07;

private:
};

class INA219 {
public:

	enum typeOfReading {BUS_VOLT, SHUNT_VOLT, CURRENT, LOAD_VOLT};

	Adafruit_INA219 ada_ina219 = Adafruit_INA219(0x41);		// Select the right I2C Address
	bool begin();
	/**
	 *get the reading of the <a href="http://www.ti.com/lit/ds/symlink/ina219.pdf">INA219</a>  sensor
	 * @param  wichReading choose wich type of readig you want
	 * @return current / voltage read
	 */
	float getReading(typeOfReading wichReading=CURRENT);

private:
};
/*! @class DS2482_100
 *  @brief class for handleling the DS18B20 temperature sensor connected to the I2C port
 *   through the DS2482-100 board. This was based on an example made by
 *   <a href="https://github.com/paeaetech/paeae.git">paeae</a>
 */
class DS2482_100 {
	//
public:
	byte data[8]; /*!< holding for onewire capture */
	byte addr[8]; /*!<  1wire wire address and CRC */
	/**
	 * start the transmission of data for the DS18B20 threw the DS2482_100
	 * @return true
	 */
	bool begin();
	/**
	 * Read the temperature of the DS18B20 threw the DS2482_100
	 * @return Tc_100 the temperature read by the DS18B20
	 */
	float getReading();
private:
};
