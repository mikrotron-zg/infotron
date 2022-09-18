#include <WiFi.h>
#include <AsyncTCP.h>
#include "Configuration.h"
#include "WebServer.h"

AsyncWebServer server(80);

/***********************************************************************
 *************************** HTTP handling *****************************
 ***********************************************************************/
void onRootRequest(AsyncWebServerRequest *request) {
  // Client root request
  IPAddress remote_ip = request->client()->remoteIP();
  DEBUG(remote_ip.toString()); DEBUG(" requested "); DEBUGLN(request->url());
  request->send(SPIFFS, "/index.html", "text/html"); // send back index page
}

void onCSSRequest(AsyncWebServerRequest *request) {
  // Client CSS request
  IPAddress remote_ip = request->client()->remoteIP();
  DEBUG(remote_ip.toString()); DEBUG(" requested "); DEBUGLN(request->url());
  request->send(SPIFFS, "/bootstrap.min.css", "text/css"); // send back CSS file
}

void onCSSMapRequest(AsyncWebServerRequest *request) {
  // Client CSS request
  IPAddress remote_ip = request->client()->remoteIP();
  DEBUG(remote_ip.toString()); DEBUG(" requested "); DEBUGLN(request->url());
  request->send(SPIFFS, "/bootstrap.min.css.map", "text/css"); // send back CSS map file
}

// TODO handle POST request

void onPageNotFound(AsyncWebServerRequest *request) {
  // Unknown request
  IPAddress remote_ip = request->client()->remoteIP();
  DEBUG(remote_ip.toString()); DEBUG(" requested "); DEBUGLN(request->url());
  request->send(404, "text/plain", "Page not found"); // send back 404
}

/***********************************************************************
 ***************************** Services ********************************
 ***********************************************************************/
void startWiFi(bool startSTA = false) {
  // Set wifi mode and start AP (and STA if needed)
  WiFi.mode(WIFI_MODE_APSTA);
  startAccessPoint();
  if (startSTA) { // start STA mode only if needed
    startWiFiStation();
  }
}

void startAccessPoint() {
  // Start access point
  WiFi.softAP(INFOTRON_SSID, INFOTRON_PASS);
  DEBUG("AP is running, ESP32 IP address: "); DEBUGLN(WiFi.softAPIP());
  sprintf(newMessage, "%03d.%03d.%03d.%03d", 
          WiFi.softAPIP()[0], WiFi.softAPIP()[1], WiFi.softAPIP()[2], WiFi.softAPIP()[3]);
  newMessageReceived = true;
}

bool startWiFiStation() {
  // Start WiFi station mode, connect to router
  if (WiFi.status() == WL_CONNECTED) return true; // already connected, nothing to do

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    DEBUGLN("Connected to primary WiFi");
    return true;
  }

  WiFi.begin(ALTERNATE_WIFI_SSID, ALTERNATE_WIFI_PASS);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    DEBUGLN("Connected to alternate WiFi");
    return true;
  }

  DEBUGLN("Not connected to any WiFi, check credentials");
  return false;
}

void startWebServer() {
  // Start web server
  startWiFi();

  // HTTP requests handling
  server.on("/", HTTP_GET, onRootRequest); // root request
  server.on("/bootstrap.min.css", HTTP_GET, onCSSRequest); // CSS request
  server.on("/bootstrap.min.css.map", HTTP_GET, onCSSMapRequest); // CSS map request
  server.onNotFound(onPageNotFound); // anything else

  server.begin();
  DEBUGLN("HTTP server started");
}