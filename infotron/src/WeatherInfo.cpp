#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "Configuration.h"
#include "WeatherInfo.h"
#include "WebServer.h"

void getWeatherInfo() {
    if (!startWiFiStation()) { // abort if no internet connection
        internetAvailable = false;
        return;
    }
    
    String url = WEATHER_API_PREFIX;
    url += "lat=" + String(LATITUDE) + "&lon=" + String(LONGITUDE) +
           "&units=metric&appid=" + WEATHER_API_KEY;
    DEBUG("sending: "); DEBUGLN(url);
    HTTPClient http;
    http.begin(url);
    int responseCode = http.GET();
    String response = "";

    if (responseCode > 0) {
        DEBUG("Response code: "); DEBUGLN(responseCode);
        response = http.getString();
        DEBUGLN(response);
    }

}