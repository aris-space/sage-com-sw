/*
Main script for ZeroG flight

v1.0, 02.10.2022
Lars Horvath
*/
#include <Servo.h>

Servo servo1;   // Mechanism 1 (Frisbee)
Servo servo2;   // Mechanism 2 (PopUp)

int init_pos1 = 140;    
int init_pos2 = 120;    

int end_pos1 = 50;
int end_pos2 = 10;

// LED pins
const int LED1 = 13;
const int LED2 = 12;

// Servo pins
const int spin1 = 9;
const int spin2 = 10;

// Button pins 
const int btn_out = 15;   // A1
const int btn_1 = 16;     // A2
const int btn_2 = 17;     // A3
const int btn_start = 19; // A5

int btn_state_1 = 0;
int btn_state_2 = 0;
int btn_state_start = 0;
int btn_laststate_start = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 1000;    // the debounce time; increase if the output flickers


// finite state machine vars
bool start_ready = 0;
int mech = 0;


// runtime
int runtime = 200;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize digital pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(btn_out, OUTPUT);
  pinMode(btn_1, INPUT_PULLDOWN);
  pinMode(btn_2, INPUT_PULLDOWN);
  pinMode(btn_start, INPUT_PULLDOWN);

  delay(50);
  digitalWrite(btn_out, HIGH);

  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10);  // attaches the servo on pin 9 to the servo object

  servo1.write(init_pos1);
  servo2.write(init_pos2);
}

void loop() {
  // Read the Button states
  btn_state_1 = digitalRead(btn_1);
  btn_state_2 = digitalRead(btn_2);
  int reading = digitalRead(btn_start);

  // Check which mechanism is executed
  if (btn_state_1 == HIGH) {
    Serial.println("Mechanism 1 (Frisbee) is selected");
    start_ready = 1;
    mech = 1;
    runtime = 50;
  }
  if (btn_state_2 == HIGH) {
    Serial.println("Mechanism 2 (PopUp) is selected");
    start_ready = 1;
    mech = 2;
    runtime = 50;
  }
  if (btn_state_1 == LOW && btn_state_2 == LOW) {
    start_ready = 0;
    mech = 0;
    runtime = 200;
  }

  // Debounce start button
  // If the switch changed, due to noise or pressing:
  if (reading != btn_laststate_start) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != btn_state_start) {
      btn_state_start = reading;

      // only toggle the LED if the new button state is HIGH
      if (btn_state_start == HIGH && start_ready == 1) {
        run_measurement(mech);
      }
    }
  }

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH); 
  delay(runtime);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(runtime);

  // save last button state
  btn_laststate_start = reading;
}

void run_measurement(int mech){
  Serial.println("Starting measurement in..");
  Serial.println("3..");
  delay(1000);
  Serial.println("2..");
  delay(1000);
  Serial.println("1..");
  if (mech == 1){
    servo1.write(end_pos1);
  }
  if (mech == 2){
    servo2.write(end_pos2);
  }
  delay(2000);
  servo1.write(init_pos1);
  servo2.write(init_pos2);
  Serial.println("measurement done! :)");

}
