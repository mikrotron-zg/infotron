/*
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * developed by Mikrotron d.o.o. (http://mikrotron.hr).
 * It contains basic weather info handler for OpenWeather 
 * (https://openweathermap.org/) API.
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

#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "Configuration.h"
#include "WeatherInfo.h"
#include "WebServer.h"


void parseWeatherInfo(String input) {
    // Parse received JSON file
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