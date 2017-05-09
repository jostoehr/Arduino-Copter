#ifndef SERVOS
#define SERVOS

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "pca9685.h"
#include <wiringPi.h>

#define SERVO_MIN 1000;
#define YAW 0
#define PITCH 1
#define ROLL 2
#define DIM 3

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

class Servo {

private:
	int m_servoId[4];
	int fid_servo;

public:
	Servo();
	void open_blaster();
	void close_blaster();
	bool Is_open_blaster();
	void init();
	void update(float, float[]);
	void stopServo();
	void setServo();

	int servoval[4];
};

extern Servo ESC;

#endif
