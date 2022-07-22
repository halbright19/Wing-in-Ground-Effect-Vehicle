/*
  sensor code created 3 Nov 2008
  by David A. Mellis
  sensor code modified 30 Aug 2011
  by Tom Igoe
  modified 10 Apr 2022
  by Helen Albright

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Ping
*/

// libraries used
#include <EEPROM.h>
#include <Servo.h>

// CONSTANTS
const int pingPin = 9;
const int servoPin = 10;
int servoPos = 1500;
int val = 0;
int addr = 0;
Servo ptchServo; //create servo object

//PID constants
double kp = -16.67;
double ki = 0;
double kd = 10;
double setPoint = 170;

//PID variables 
unsigned long currentTime, previousTime;
double timeInterval;
double ptchPE, ptchIE, ptchDE, ptchPE_prev;
double output;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  //intialize servo
  ptchServo.attach(servoPin);
  ptchServo.writeMicroseconds(servoPos);

  // intialize EEPROM
  delay(5000); // 5 second delay before it clears the data
  for (int i = 0; i < EEPROM.length(); i++)
    EEPROM.write(i, 0);
  //test message
  Serial.print("EEPROM data cleared");
  Serial.println();
}

void loop() {
  while (addr < EEPROM.length()) {
    // establish variables for duration of the ping, and the distance result
    // in centimeters
    long duration, cm;

    // The sensor is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);

    // The same pin is used to read the signal from the sensor: a HIGH pulse
    // whose duration is the time (in microseconds) from the sending of the ping
    // to the reception of its echo off of an object.
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
    cm = microsecondsToCentimeters(duration); // convert the time into a distance

    //PID loop
    output = computePID(cm);
    ptchServo.writeMicroseconds(output);
    
    //print out of data
    Serial.print("cm: ");
    Serial.print(cm);
    Serial.print("\t");
    Serial.print("servopos: ");
    Serial.print(output); 
    Serial.println();

    //Write data to EEPROM
    EEPROM.write(addr,cm); //save height to EEPROM
    EEPROM.write((addr +1), output); //save servo position to EEPROM
    addr += 2;
    delay(100); //delay 100 miliseconds
  }
  exit(0);
}

//FUNCTIONS
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

double computePID(double ptch){
  currentTime = millis()*1000; //get current time in microseconds
  timeInterval = (double)(currentTime-previousTime); //compute elapsed time
  previousTime = currentTime; //remember current time
  
  //calculations
  ptchPE = ptch - setPoint; //proportional error
  ptchIE = ptchIE + ptchPE * timeInterval; //integral error
  ptchDE = (ptchPE - ptchPE_prev)/timeInterval; //differential error
  ptchPE_prev = ptchPE; //remember current error

  //set servo position
  servoPos = 1500 + (ptchPE*kp) + (ptchIE*ki) + (ptchDE*kd);
  return servoPos;
}
