/** Main Code of the DIY Drone Project "Phoenix"
 *  
 *  @author: Johannes Stöhr
 *  @e-mail: post@johannes-stoehr.de
 *  @version: 24-07-2017
 */
 
#include <XBee.h>
#include <Servo.h>
#include <PID_v1.h>
#include <Thread.h>
#include <StaticThreadController.h>
#include "config.h"

/* ================================================= */
/* ------------------- GLOBAL VAR ------------------ */
/* ================================================= */

// XBEE
XBee xbee = XBee();
uint8_t option = 0;
uint8_t *data;

// ESC 
Servo esc1, esc2, esc3, esc4;
boolean motorsOn = false;
int tmp = 0;
int x_speed_joy1 = 0;

// IMU/DMP
#define YAW 0
#define PITCH 1
#define ROLL 2

bool dmpReady = false;  // set true if DMP init was successful
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// PID 
double pid_roll_in,   pid_roll_out,   pid_roll_setpoint = 0;
double pid_pitch_in,  pid_pitch_out,  pid_pitch_setpoint = 0;
double pid_yaw_in,    pid_yaw_out,    pid_yaw_setpoint = 0;

// THREADS
Thread dmpThread = Thread();
Thread controlThread = Thread();
StaticThreadController<2> controller (&dmpThread, &controlThread);

/* ================================================= */
/* ------------------ PROTOTYPES ------------------- */
/* ================================================= */

void initializeServo();
void setServo(Servo esc, int value);
void setAllServo(int value);
void getRxPacket();
boolean initDMP();
void getAttitude();
void pid_initialize();
void pid_update();
void pid_compute();

/* ================================================= */
/* --------------------- SETUP --------------------- */
/* ================================================= */

void setup() {
  Serial.begin(9600);
  xbee.setSerial(Serial);
  
  initializeServo();
  initDMP();
  pid_initialize();
  
  dmpThread.onRun(getAttitude);
  dmpThread.setInterval(1);

  controlThread.onRun(getRxPacket);
  controlThread.setInterval(25);

  delay(1000);
}

/* ================================================= */
/* ------------------- MAIN LOOP ------------------- */
/* ================================================= */

void loop() {
    controller.run();
    tmp = x_speed_joy1;
    x_speed_joy1 = data[0]*256 + data[1];
    if(x_speed_joy1 < 4 || x_speed_joy1 > 2000) {
      x_speed_joy1 = tmp;
    }
    x_speed_joy1 = map(x_speed_joy1, 4, 1018, 1150, 2000);
    //int x_speed_joy1 = 1200;
    pid_update();
    pid_compute();

    setServo(esc1, x_speed_joy1 + pid_pitch_out);
    setServo(esc2, x_speed_joy1 + pid_roll_out);
    setServo(esc3, x_speed_joy1 - pid_pitch_out);
    setServo(esc4, x_speed_joy1 - pid_roll_out);
    //setAllServo(x_speed_joy1);

    /*Serial.print(ypr[0] * 180/M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180/M_PI);
    Serial.print("\t");
    Serial.println(ypr[2] * 180/M_PI);

    Serial.println(x_speed_joy1);
  */
}
