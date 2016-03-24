/*
 * MHZ19.cpp
 *
 *  Created on: 19.03.2016
 *      Author: Andrey Vetlugin <antrew@gmail.com>
 */

//#include <Arduino.h>
#include "MHZ19.h"
//#include <SoftwareSerial.h>

MHZ19::MHZ19(int pwm_input_pin, int rx_pin, int tx_pin) {
	PWM_INPUT_PIN = pwm_input_pin;
	RX_PIN = rx_pin;
	TX_PIN = tx_pin;
	init();
}

MHZ19::MHZ19(int pwm_input_pin) {
	PWM_INPUT_PIN = pwm_input_pin;
	RX_PIN = 0;
	TX_PIN = 0;
	init();
}

MHZ19::MHZ19(int rx_pin, int tx_pin) {
	PWM_INPUT_PIN = 0;
	RX_PIN = rx_pin;
	TX_PIN = tx_pin;
	init();
}

void MHZ19::init() {
	// init PWM protocol
	if (PWM_INPUT_PIN) {
		pinMode(PWM_INPUT_PIN, INPUT);
	}
	// init Serial protocol
	if (RX_PIN && TX_PIN) {
		serial = new SoftwareSerial(TX_PIN, RX_PIN);
		serial->begin(9600);
	}
}

boolean MHZ19::low() {
	return LOW == digitalRead(PWM_INPUT_PIN);
}

boolean MHZ19::high() {
	return HIGH == digitalRead(PWM_INPUT_PIN);
}

float MHZ19::readPpm() {
	// TODO automagically decide on the method
}

float MHZ19::readPpmPwm() {
	unsigned long lowCounter = 0;
	unsigned long highCounter = 0;

	// wait for low
	while (high()) {
	}

	// wait for high
	while (low()) {
	}

	// count high iterations
	while (high()) {
		highCounter++;
	}

	// count low iterations
	while (low()) {
		lowCounter++;
	}

	float ppm = 5000.0 * (1002.0 * highCounter - 2.0 * lowCounter) / 1000.0
			/ (highCounter + lowCounter);

	Serial.print("high = ");
	Serial.print(highCounter);
	Serial.print(" ; low = ");
	Serial.print(lowCounter);
	Serial.print(" ; high+low = ");
	Serial.print(highCounter + lowCounter);
	Serial.print(" ; ppm = ");
	Serial.print(ppm);
	Serial.println();

	return ppm;
}

float MHZ19::readPpmSerial() {
	byte cmd[9] = { 0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79 };
	// command to ask for data
	char response[9]; // for answer

	serial->write(cmd, 9);
	serial->readBytes(response, 9);
}

MHZ19::~MHZ19() {
}
