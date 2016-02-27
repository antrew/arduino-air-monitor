#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AM2320.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

AM2320 temperatureSensor;

float i = 0;

void setup() {
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
}

void loop() {
	// Do nothing here...
//	lcd.print
	delay(1000);
	lcd.clear();
	lcd.print(i);
	i += 0.01F;
	float temperature = temperatureSensor.getTemperature();
	lcd.setCursor(0, 1);
	lcd.print("T = ");
	lcd.print(temperature);
	lcd.print(" C");
	lcd.setCursor(0, 2);
	lcd.print("H = ");
	float humidity = temperatureSensor.getHumidity();
	lcd.print(humidity);
	lcd.print(" %");
}
