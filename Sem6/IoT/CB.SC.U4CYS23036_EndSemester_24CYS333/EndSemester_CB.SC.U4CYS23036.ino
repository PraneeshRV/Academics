#include <Arduino.h>
const int HEIGHT = 100; 
const int LOW_T = 50;  
const int HIGH_T = 90; 

long getDistance() {
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  
  long time = pulseIn(6, HIGH);
  return time * 0.034 / 2;
}

void setup() {
  Serial.begin(9600); 
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  }

void loop() {
  long distance = getDistance();
  
  int waterHeight = HEIGHT - distance;
  if (waterHeight < 0) waterHeight = 0;
  
  float percentage = ((float)waterHeight / HEIGHT) * 100;

  Serial.print("Distance: "); 
  Serial.print(distance); 
  Serial.print("Water Level: "); 
  Serial.print(percentage); 

  if (percentage <= LOW_T) {
    Serial.println("LOW WATER LEVEL!");
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  } 
  else if (percentage >= HIGH_T) {
    Serial.println("TANK NEARLY FULL!");
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
  } 
  else {
    Serial.println("Level Normal");
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  delay(1000);
}
