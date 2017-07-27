
#define PWM_ESC1 3
#define PWM_ESC2 5
#define PWM_ESC3 6
#define PWM_ESC4 9

void initializeServo() {
  esc1.attach(PWM_ESC1);
  esc2.attach(PWM_ESC2);
  esc3.attach(PWM_ESC3);
  esc4.attach(PWM_ESC4);
  setAllServo(0);
}

void setAllServo(int value) {
  esc1.writeMicroseconds(value);
  esc2.writeMicroseconds(value);
  esc3.writeMicroseconds(value);
  esc4.writeMicroseconds(value);
}

void setServo(Servo esc, int value) {
  esc.writeMicroseconds(value);
}





