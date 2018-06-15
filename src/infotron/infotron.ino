/*Arduino IDE settings for Croduino NOVA:
  First select Tools->Board->Generic ESP8266 Module.
  Then select Tools->Flash Size->4M (1MSPIFFS) and 
  Tools->Reset Method->nodemcu.
  Finaly, select Tools->Port->[Port number, e.g. COM1, dev/ttyUSB0 etc.]
  Also, set your Serial Monitor baud rate to 115200.*/

#include "credentials.h" // enter your wifi credentials in this file first
#include "web_page.h" // web page content
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <MD_Parola.h> 
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Ticker.h> 

ESP8266WebServer web_server(80); // web server on port 80

/* Define the number of devices we have in the chain and the hardware interface
   NOTE: These pin numbers are for Croduino NOVA hardware SPI and will probably not
   work with different hardware and may need to be adapted*/
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // works only with MD_MAX72xx 3.0.0 and up
#define MAX_DEVICES 4
#define CLK_PIN   14 // or SCK
#define DATA_PIN  13 // or MOSI
#define CS_PIN    15 // or SS

// HARDWARE SPI
MD_Parola mdp = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Scrolling parameters
uint8_t scrollSpeed = 30;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 20; // in milliseconds

// Global message buffers shared by Wifi and Scrolling functions
#define BUF_SIZE  512
char curMessage[BUF_SIZE] = {"Infotron starting..."};
char newMessage[BUF_SIZE] = {""};
bool newMessageAvailable = false;

// Start and timeout values
bool start = true;
Ticker timer;
const float wifi_timeout = 30.0; // how long to wait for wifi connection (in seconds)

// Define debug statements for the serial output
#define  DEBUG  1 //0 - debug off, 1 - debug on
#if DEBUG
#define prnt(x) Serial.print(x) // in debug mode all prnt statements will be sent to Serial Monitor
#else
#define prnt(x) // when debug mode is off, this does nothing
#endif

void checkConnection(){
  // Check to see if we're connected to WiFi
  if (WiFi.status() == WL_CONNECTED){
    prnt("\nConnected to the wifi! IP address is: ");  
    prnt(WiFi.localIP());
    sprintf(newMessage, "%03d.%03d.%03d.%03d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
    newMessageAvailable = true;
    web_server.on("/", handleWebRequest); // define web server handler
    web_server.begin(); // start web server
    start = false;
    timer.detach();
  }

}

void wifiTimeout(){
  // If this is triggered and we're still not connected to the WiFi, there's something wrong!
  if (start){
    prnt("Could not connect to WiFi, please check settings in credentials.h");
    strcpy(newMessage, "Could not connect to WiFi, please check settings in credentials.h");
    newMessageAvailable = true;
    start = false;
  }
  prnt("\nTimer triggered!");
  timer.detach();
}

void handleWebRequest(){
  // What to do with GET request
  String content = WEB_PAGE; // read web page content
  web_server.send(200, "text/html", content); // replay
}

void setup() {

  Serial.begin(115200); // Starting Serial Monitor connection
  delay(10);
 
  prnt("\nInfotron starting!");
  
  // Initailizing MD_Parola
  mdp.begin();
  mdp.displayClear();
  mdp.displaySuspend(false);


  // Show start message
  mdp.displayScroll(curMessage, scrollAlign, scrollEffect, scrollSpeed);

  prnt("\nConnecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  prnt("\nStarting timeout timer...");
  timer.attach(wifi_timeout, &wifiTimeout); //start timer
}

void loop() {

  if (start) checkConnection();
  
  web_server.handleClient();
  
  if (mdp.displayAnimate()) {
    if(newMessageAvailable){
      prnt("\nNew message:");
      prnt(newMessage);
      strcpy(curMessage, newMessage);
      newMessageAvailable = false;
    }
    mdp.displayReset();
  }
  
}



