/*
  INFOTRON
  Simple info screen based on ESP32 and LED matrix display, controlled via integrated web app

  Author: Tomislav Preksavec, Mikrotron d.o.o. Zagreb, mikrotron@mikrotron.hr
  Date: 11/2021
  License: GNU GPL v3 - please see the LICENSE file on the project root for more details

*/

#include <Arduino.h>
#include <MD_Parola.h> 
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Configuration.h"

/* 
  Define the number of devices we have in the chain and the hardware interface SPI connection pins
  NOTE: These pin numbers are for D1 MINI ESP 32 hardware SPI and will probably not
        work with different hardware and may need to be adapted
*/
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // works only with MD_MAX72xx 3.0.0 and up
#define MAX_DEVICES   4   // number of 8x8 LED matrix displays in use
#define CLK_PIN       18  // pinout tag: SCK
#define DATA_PIN      23  // pinout tag: MOSI
#define CS_PIN        5   // pinout tag: SS

MD_Parola screen = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Scrolling parameters
uint8_t frameDelay = 30;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;

// Global message buffers
#define BUF_SIZE  1024 // buffer size that should be able to handle data, increase size if needed
char curMessage[BUF_SIZE] = {"Infotron starting..."}; // message currently on display
char newMessage[BUF_SIZE] = {"New message"}; // next message to display

void setup() {
  // Read instructions on DEBUG_MODE in 'include/Debug.h' file
  #ifdef DEBUG_MODE
    Serial.begin(115200);
    delay(3000);
    DEBUGLN("Infotron started in debug mode");
  #endif
  // Initailizing MD_Parola
  screen.begin();
  screen.displayClear();
  screen.displaySuspend(false);

  // Show start message
  screen.displayScroll(curMessage, scrollAlign, scrollEffect, frameDelay);
}

void loop() {
  if (screen.displayAnimate()) {
    strcpy(curMessage, newMessage);
    screen.displayScroll(curMessage, scrollAlign, scrollEffect, frameDelay);
    screen.displayReset();
  }
}