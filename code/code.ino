// Includes the Servo library
#include <Servo.h>
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int alarmPin = 7;
const int ledPin_1 = 8;
const int trigPin = 10;
const int echoPin = 11;

unsigned long currentMillis;
unsigned long previousMillis = 0;
bool obj =  false;

// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
void setup() {
  // Setup U-Sonic sensor pin
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  // Setup LED pin
  pinMode(ledPin_1, OUTPUT);
  digitalWrite(ledPin_1, LOW);
  
  // Setup Alarm pin
  pinMode(alarmPin, OUTPUT);
  digitalWrite(alarmPin, HIGH);

  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  actionCheck();

  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  actionCheck();

  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void actionCheck() {
  if (distance <= 20) {
    
    if (obj == false){
      obj = true;
    }
    else  {
      currentMillis = millis();
      long duration = currentMillis - previousMillis;
      // Serial.println(duration);
      if (duration >= 3000){
        digitalWrite(ledPin_1, HIGH);
        if (duration >= 6000) {
          digitalWrite(alarmPin, LOW);
        }
      }

    }
  }
  else{
    resetAlarmState();
    resetTimer();
    obj = false;
  }
}

void resetTimer() {
  previousMillis = currentMillis;
}

void resetAlarmState() {
  digitalWrite(ledPin_1, LOW);
  digitalWrite(alarmPin, HIGH);
}