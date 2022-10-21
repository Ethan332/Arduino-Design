// CreaTechWeb : Displaying an image on a TFT screen with arduino

// https://createchweb.com/displaying-an-image-on-a-tft-screen-with-arduino/

// include the necessary libraries
#include <SPI.h>
#include <SD.h>
#include <TFT.h>  // Arduino LCD library
#include <Wire.h>


// pin definition for the Uno
#define sd_cs  4
#define lcd_cs 10
#define dc     9
#define rst    8

int degree[3] = {375, 375, 375};


TFT TFTscreen = TFT(lcd_cs, dc, rst);

// this variable represents the image to be drawn on screen
PImage logo;
PImage logo2; //xin de

boolean isAnamationFinished = true;
int movex = 1;
int dist[3] = {1, -1, 1};
int whichAnimationPlay = 0;

void setup() {
  // initialize the GLCD and show a message
  // asking the user to open the serial line
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);

  TFTscreen.stroke(0, 0, 255);
  TFTscreen.println();
  TFTscreen.println(F("Arduino TFT Bitmap Example"));
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.println(F("Open serial monitor"));
  TFTscreen.println(F("to run the sketch"));

  // initialize the serial port: it will be used to
  // print some diagnostic info
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial port to connect. Needed for native USB port only
  }

  // clear the GLCD screen before starting
  TFTscreen.background(255, 255, 255);

  // try to access the SD card. If that fails (e.g.
  // no card present), the setup process will stop.
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(sd_cs)) {
    Serial.println(F("failed!"));
    return;
  }
  Serial.println(F("OK!"));

  // initialize and clear the GLCD screen
  TFTscreen.begin();
  TFTscreen.background(255, 255, 255);

  // now that the SD card can be access, try to load the
  // image file.
  logo = TFTscreen.loadImage("eyeshot.bmp");
  TFTscreen.image(logo, 0, 0);

  if (!logo.isValid()) {
    Serial.println(F("error while loading arduino.bmp"));
  }
}

void loop() {
  // don't do anything if the image wasn't loaded correctly.
  if (logo.isValid() == false) {
    return;
  }
  

  int x1 = random(3);
  if (x1 == 0 && isAnamationFinished == true) {
    isAnamationFinished = false;
    whichAnimationPlay = 1;

  } else if (x1 == 1 && isAnamationFinished == true) {
    isAnamationFinished = false;
    isAnamationFinished = false;
    whichAnimationPlay = 2;

  } else if (x1 == 2 && isAnamationFinished == true) {
    isAnamationFinished = false;
    isAnamationFinished = false;
    whichAnimationPlay = 3;

  }

  animationPlay();
  delay(300);
}

void animationPlay(_index) {
  switch (whichAnimationPlay) {
    case 1:
      randomAnimation1();
      break;
    case 2:
      randomAnimation2();
      break;
    case 3:
      randomAnimation3();
      break;
    default:
      break;
  }
}
void randomAnimation1() {

  //code
  if (movex == 64) {
    dist[0] *= -1;
  }
  movex += dist[0];

  if (movex == -1) {
    isAnamationFinished = true;
    dist[0] *= -1;
    movex = 0;
  }
  TFTscreen.image(logo, movex, 0);
}

void randomAnimation2() {
  //code
  if (movex == -64) {
    dist[1] *= -1;
  }
  movex += dist[1];

  if (movex == 1) {
    isAnamationFinished = true;
    dist[1] *= -1;
    movex = 0;
  }
  TFTscreen.image(logo, movex, 0);

}
void randomAnimation3() {
  movex += 1;
  if (movex == 200) {
    isAnamationFinished = true;
    movex = 0;
  }
  TFTscreen.image(logo, 0, 0);
}
