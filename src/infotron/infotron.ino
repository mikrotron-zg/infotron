/*Arduino IDE settings for Croduino NOVA:
  First select Tools->Board->Generic ESP8266 Module.
  Then select Tools->Flash Size->4M (1MSPIFFS) and 
  Tools->Reset Method->nodemcu.
  Finaly, select Tools->Port->[Port number, e.g. COM1, dev/ttyUSB0 etc.]
  Also, set your Serial Monitor baud rate to 115200.
*/

#include "credentials.h" //enter your wifi credentials in this file first
#include "ESP8266WiFi.h"
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define debug statements for the serial output
#define  DEBUG  1 //0 - debug off, 1 - debug on
#if DEBUG
#define prnt(x) Serial.print(x)
#else
#define prnt(x)
#endif

const char* ssid = WIFI_SSID;  
const char* pass = WIFI_PASS;  

void setup() {

  Serial.begin(115200); 
  delay(10);
  prnt("\nInfotron starting!");
  prnt("\nConnecting to WiFi...");
    
  WiFi.begin(ssid, pass); 
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    prnt(".");
  }
  
  prnt("\nConnected to the wifi! IP address is: ");  
  prnt(WiFi.localIP());

}

void loop() {
  

}
