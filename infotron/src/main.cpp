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
#include "WebServer.h"
#include "DateTimeHandler.h"

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
DisplayMode displayMode = TEXT;

// Scrolling parameters
uint8_t frameDelay = 30;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;

// Global message buffers
#define BUF_SIZE  1024 // buffer size that should be able to handle data, increase size if needed
char curMessage[BUF_SIZE] = {""}; // message currently on display
char newMessage[BUF_SIZE] = {"Infotron starting..."}; // next message to display
bool newMessageReceived = true;

// Global datetime container
uint16_t datetime[6] = {0, 0, 0, 0, 0, 0}; // day, month, year, hour, minute, second
bool datetimeUpdated = false;

// Global weather info container
WeatherInfo weatherInfo = {0, 0, 0, false, 0};

void displayText() {
  // Handle custom text display
  if (newMessageReceived) {
    strcpy(curMessage, newMessage);
    newMessageReceived = false;
    screen.displayScroll(curMessage, scrollAlign, scrollEffect, frameDelay);
  }
}

void displayDateTime() {
  // Handle date/time display
  if (datetimeUpdated) {
    validateTime();
    if (datetime[5] == 20 || datetime[5] == 40) { // show date
      sprintf(newMessage, "%02d.%02d.%04d.", datetime[0], datetime[1], datetime[2]);
      datetimeUpdated = false;
      screen.displayClear();
      screen.displayScroll(newMessage, scrollAlign, scrollEffect, frameDelay*1.5);
      return;
    }
    if (datetime[5]%2 == 0) { // show time
      sprintf(curMessage, "%02d:%02d", datetime[3], datetime[4]);
    } else {
      sprintf(curMessage, "%02d %02d", datetime[3], datetime[4]);
    }
    datetimeUpdated = false;
    screen.displayText(curMessage, PA_CENTER, screen.getSpeed(), 0, PA_NO_EFFECT, PA_NO_EFFECT);
  }
}

void displayWeatherInfo() {
  // Handle weather info display
  if (!weatherInfo.isValid) { // no internet connection or server failure
    sprintf(newMessage, "Can't access weather data");
    newMessageReceived = true;
    displayMode = TEXT;
    return;
  }

  if (weatherInfo.showing == 0) { // first time showing weather info
    sprintf(curMessage, "%d \xB0""C", weatherInfo.temp);
    screen.displayText(curMessage, PA_CENTER, screen.getSpeed(), MAX_SCREEN_TIME, PA_GROW_UP, PA_GROW_DOWN);
    weatherInfo.showing++;
    return;
  }

  switch (weatherInfo.showing) {
    // TODO
    case 1:
      sprintf(curMessage, "%d%% RH", weatherInfo.humidity);
      screen.displayText(curMessage, PA_CENTER, screen.getSpeed(), MAX_SCREEN_TIME, PA_GROW_UP, PA_GROW_DOWN);
      weatherInfo.showing++;
      break;
    case 2:
      sprintf(curMessage, "%dhPa", weatherInfo.pressure);
      screen.displayText(curMessage, PA_CENTER, screen.getSpeed(), MAX_SCREEN_TIME, PA_GROW_UP, PA_GROW_DOWN);
      weatherInfo.showing++;
      break;
    case 3:
      sprintf(curMessage, "%d \xB0""C", weatherInfo.temp);
      screen.displayText(curMessage, PA_CENTER, screen.getSpeed(), MAX_SCREEN_TIME, PA_GROW_UP, PA_GROW_DOWN);
      weatherInfo.showing = 1;
      break;
  }
}

void setup() {
  // Read instructions on DEBUG_MODE in 'include/Debug.h' file
  #ifdef DEBUG_MODE
    Serial.begin(115200);
    delay(3000);
    DEBUGLN("Infotron started in debug mode");
  #endif

  // Mount SPIFFS file system
  if(!SPIFFS.begin()){
    DEBUGLN("SPIFFS mounting error");
  }

  // Initailizing MD_Parola
  screen.begin();
  screen.displayClear();
  screen.displaySuspend(false);

  // Show start message
  displayText();

  // Start web server
  startWebServer();
}

void loop() {
  if (screen.displayAnimate()) {
    switch (displayMode) {
      case TEXT:
        displayText();
        screen.displayReset();
        break;
      case DATETIME:
        displayDateTime();
        break;
      case WEATHER:
        displayWeatherInfo();
        break;
    } 
    
  }
}