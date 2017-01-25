#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AM2320.h>
#include <MHZ19.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

AM2320 temperatureSensor;

int MHZ19_PWM_INPUT_PIN = 2;

MHZ19 mhz19 = MHZ19(MHZ19_PWM_INPUT_PIN);

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

	temperatureSensor.Read();
	float temperature = temperatureSensor.t;
	float humidity = temperatureSensor.h;
	float ppm = mhz19.readPpm();

	Serial.print("T = ");
	Serial.print(temperature);
	Serial.print(" C ; H = ");
	Serial.print(humidity);
	Serial.print(" % ; CO2 = ");
	Serial.print(ppm);
	Serial.println(" ppm");

	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print(temperature);
	lcd.print(" C ");
	lcd.print(humidity);
	lcd.print(" %");

	lcd.setCursor(0, 1);
	lcd.print(ppm);
	lcd.print(" ppm");
}
