#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AM2320.h>
#include "MHZ19.h"

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

AM2320 temperatureSensor;

int MHZ19_PWM_INPUT_PIN = 2;
int MHZ19_RX_PIN = 3; // our serial TX
int MHZ19_TX_PIN = 4; // our serial RX

MHZ19 mhz19 = MHZ19(MHZ19_PWM_INPUT_PIN);

MHZ19 mhz19serial = MHZ19(MHZ19_RX_PIN, MHZ19_TX_PIN);

float i = 0;

void setup() {
	Serial.begin(115200);
	Serial.println("Temperature, Humidity, CO2");

	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
}

void loop() {
	delay(1000);

	i += 0.01F;
	float temperature = temperatureSensor.getTemperature();
	float humidity = temperatureSensor.getHumidity();
	float ppmPwm = mhz19.readPpmPwm();
	float ppmSerial = mhz19serial.readPpmSerial();

	lcd.clear();
	lcd.print(i);

	lcd.print(" ");
	lcd.print(ppmSerial);

	lcd.setCursor(0, 1);
	lcd.print("T = ");
	lcd.print(temperature);
	lcd.print(" C");

	lcd.setCursor(0, 2);
	lcd.print("H = ");
	lcd.print(humidity);
	lcd.print(" %");

	lcd.setCursor(0, 3);
	lcd.print("CO2 = ");
	lcd.print(ppmPwm);
	lcd.print(" ppm");
}
