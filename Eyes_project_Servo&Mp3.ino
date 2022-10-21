// include the necessary libraries
#include <SPI.h>
#include <hcsr04.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//MP3 Player 
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMID  375

//ultrasonic sensor x3
#define TRIG_PIN 7
#define ECHO_PIN 8

#define TRIG_PIN 9
#define ECHO_PIN 10

#define TRIG_PIN 11
#define ECHO_PIN 12

// Use pins 2 and 3 to communicate with DFPlayer Mini

static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;






HCSR04 hcsr4(TRIG_PIN, ECHO_PIN, 20, 4000);
unsigned int myDistance = 1000;//compareed distance 
int num = 1;
int degree[3] = {375, 375, 375};

void setup() {
  // initialize the serial port: it will be used to
  // print some diagnostic info
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }
  pwm.begin();
  pwm.setPWMFreq(60);
  for (int i = 0; i < num; i++) {
    pwm.setPWM(i, 0, degree[i]);
  }

  softwareSerial.begin(9600);//mp3
  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)
     ) {
      player.volume(8);

    //    Serial.println("OK");
    // Set volume to maximum (0 to 30).
    //player.volume(20);
    // Play the "0001.mp3" in the "mp3" folder on the SD card
    // player.playMp3Folder(3);
    // player.setTimeOut(500); //Set serial communictaion time out 500ms

  }
  //
  
  else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  
}

void loop() {
  // don't do anything if the image wasn't loaded correctly.  

  //没看到人
  if (hcsr4.distanceInMillimeters() > myDistance) {
    for (int i = 0; i < num; i++) {
      degree[i] += random(-4, 4);
      pwm.setPWM(i, 0, degree[i]);
      playSound1();
    }

  }

  //看到人
  if (hcsr4.distanceInMillimeters() < myDistance) {
    for (int i = 0; i < num; i++) {
      degree[i] = SERVOMID;
      pwm.setPWM(i, 0, degree[i]);
      playSound2();
    }
  }
  delay(300);
}

void playSound1() {
  player.loop(1);
  player.volume(2);
}
void playSound2() {
  player.loop(2);
  player.volume(2);
}
