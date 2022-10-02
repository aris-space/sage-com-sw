/*
LED Test script

Lars Horvath
*/

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(8, HIGH);  
  delay(500);
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  delay(500); 
}
