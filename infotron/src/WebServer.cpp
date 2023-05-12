/*
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * developed by Mikrotron d.o.o. (http://mikrotron.hr).
 * It contains basic web server HTTP handling, needs files from data 
 * directory to be uploaded to ESP32 SPIFFS in order to work properly.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. See the LICENSE file at the 
 * top-level directory of this distribution for details 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <WiFi.h>
#include <AsyncTCP.h>
#include <HTTPClient.h>
#include "Configuration.h"
#include "WebServer.h"
#include "DateTimeHandler.h"
#include "WeatherInfo.h"

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

void onPostRequest(AsyncWebServerRequest *request) {
  // Client POST request
  DEBUGLN("Got post request");
  if (request->params() == 0) {
    DEBUGLN("No parameters in post request!");
    request->send(404);
    return;
  }
  AsyncWebParameter* p = request->getParam(0);
  String param = p->name();
  DEBUG("Parameter name: "); DEBUGLN(param); 
  DEBUG("Parameter value: "); DEBUGLN(p->value());

  // Handle parameters
  if (param == "text") {
    // show custom text
    strcpy(newMessage, p->value().c_str());
    newMessageReceived = true;
    if (displayMode == DATETIME) stopDateTime();
    displayMode = TEXT;
  } else if (param == "time") {
    // show datetime
    startDateTime(p->value());
    displayMode = DATETIME;
  } else if (param == "weather") {
    // get weather data
    getWeatherInfo();
    if (displayMode == DATETIME) stopDateTime();
    displayMode = WEATHER;
  } else {
    DEBUGLN("Parameter unknown!");
    request->send(404);
    return;
  }

  request->send(200);
}

void onPageNotFound(AsyncWebServerRequest *request) {
  // Unknown request
  IPAddress remote_ip = request->client()->remoteIP();
  DEBUG(remote_ip.toString()); DEBUG(" requested "); DEBUGLN(request->url());
  request->send(404, "text/plain", "Page not found"); // send back 404
}

/***********************************************************************
 ***************************** Services ********************************
 ***********************************************************************/
void startAccessPoint() {
  // Start access point
  WiFi.softAP(INFOTRON_SSID, INFOTRON_PASS);
  DEBUG("AP is running, ESP32 IP address: "); DEBUGLN(WiFi.softAPIP());
  sprintf(newMessage, "My IP address: %d.%d.%d.%d", 
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

void startWiFi(bool startSTA = false) {
  // Set WiFi mode and start AP (and STA if needed)
  WiFi.mode(WIFI_MODE_APSTA);
  startAccessPoint();
  if (startSTA) { // start STA mode only if needed
    startWiFiStation();
  }
}

void startWebServer() {
  // Start WiFi
  startWiFi(true);

  // HTTP requests handling
  server.on("/", HTTP_GET, onRootRequest); // root request
  server.on("/bootstrap.min.css", HTTP_GET, onCSSRequest); // CSS request
  server.on("/bootstrap.min.css.map", HTTP_GET, onCSSMapRequest); // CSS map request
  server.on("/infotron", HTTP_POST, onPostRequest);
  server.onNotFound(onPageNotFound); // anything else

  server.begin();
  DEBUGLN("HTTP server started");
}

String getApiResponse(String url, String headerName, String headerValue) {
  String response = "";

  // Return empty string if there is no WiFi connection
  if (!startWiFiStation()) return response;

  HTTPClient http;
  if (headerName != "") http.addHeader(headerName, headerValue);
  http.begin(url);
  int responseCode = http.GET();

  DEBUG("Response code: "); DEBUGLN(responseCode);
  if (responseCode > 0) { 
      response = http.getString();
      DEBUGLN(response);
  }

  return response;
}