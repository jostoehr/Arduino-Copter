/* RC-Controller-Code */
#include <XBee.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

XBee xbee = XBee();

uint8_t payload[] = { 0, 0 };

// 16-bit addressing: Enter address of remote XBee, typically the coordinator
Tx16Request tx = Tx16Request(0x5678, payload, sizeof(payload));

// 64-bit addressing: This is the SH + SL address of remote XBee
//XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x4008b490);
// unless you have MY on the receiving radio set to FFFF, this will be received as a RX16 packet
//Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();

#define SW_JOY1 2 // digital pin connected to switch output
#define X_JOY1 0 // analog input of X-Joystick1 for speed
#define OLED_RESET 4 // not used 
Adafruit_SSD1306 display(OLED_RESET);

int x_joy1 = 0;
boolean motorsOn = false;

boolean checkSuccessResponse();
void initDisplay();
void displayMotorsOff();
void displayMotorsOn();

void setup()
{
  pinMode(SW_JOY1, INPUT);
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //initDisplay();
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop()
{
  /*if(digitalRead(SW_JOY1) == LOW) {
    if(motorsOn) {
      payload[0] = 'm';
      motorsOn = false;
      //displayMotorsOff();
    } else {
      payload[0] = 'M';
      motorsOn = true;
      //displayMotorsOn();
    }
  } else {*/
    // break down 10-bit reading into two bytes and place in payload
    x_joy1 = analogRead(X_JOY1);
    Serial.println(x_joy1);
    payload[0] = x_joy1 >> 8 & 0xff;
    payload[1] = x_joy1 & 0xff;
  //}
  xbee.send(tx);
  //checkSuccessResponse();*/
}
