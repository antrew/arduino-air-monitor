/*
 * MHZ19.h
 *
 *  Created on: 19.03.2016
 *      Author: Andrey Vetlugin <antrew@gmail.com>
 */

#ifndef MHZ19_H_
#define MHZ19_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

class MHZ19 {
public:
	MHZ19(int pwm_input_pin, int rx_pin, int tx_pin);
	MHZ19(int pwm_input_pin);
	MHZ19(int rx_pin, int tx_pin);
	float readPpm();
	float readPpmPwm();
	float readPpmSerial();
	virtual ~MHZ19();
private:
	int PWM_INPUT_PIN;
	int RX_PIN;
	int TX_PIN;
	SoftwareSerial *serial;
	void init();
	boolean low();
	boolean high();
};

#endif /* MHZ19_H_ */
