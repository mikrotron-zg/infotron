#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "Configuration.h"
#include "WeatherInfo.h"
#include "WebServer.h"


void parseWeatherInfo(String input) {
    JSONVar root = JSON.parse(input);
    if (JSON.typeof(root) == "undefined") {
        DEBUGLN("Parsing input failed!");
        weatherInfo.isValid = false;
        return;
    }

    JSONVar main = root["main"]; // we only need basic weather info
    JSONVar keys = main.keys();
    weatherInfo.temp = (double)main[keys[0]] + 0.5;
    weatherInfo.pressure = main[keys[4]];
    weatherInfo.humidity = main[keys[5]];
    weatherInfo.isValid = true;
    weatherInfo.showing = 0;
}

void getWeatherInfo() {
    // Send API call to weather info provider
    if (!startWiFiStation()) { // abort if no internet connection
        weatherInfo.isValid = false;
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

    DEBUG("Response code: "); DEBUGLN(responseCode);
    if (responseCode > 0) { 
        response = http.getString();
        DEBUGLN(response);
        parseWeatherInfo(response);
    } else {
        weatherInfo.isValid = false;
    }
}