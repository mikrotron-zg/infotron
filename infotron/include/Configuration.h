/*
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * developed by Mikrotron d.o.o. (http://mikrotron.hr).
 * It contains global variables, settings and includes needed for multiple
 * project modules.
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

#ifndef CONFIGURATION_H
    #define CONFIGURATION_H
    // Settings
    #define DEBUG_MODE // comment out for production, read the instructions in include/Debug.h file
    #define MAX_SCREEN_TIME 5000 // in miliseconds
    #define CRYPTO_NUM 2   // number of crypto currencies we're tracking

    // Includes
    #include <SPIFFS.h>
    #include <ESPAsyncWebServer.h>
    #include "Debug.h"

    // Display mode enum
    typedef enum {
        TEXT,
        DATETIME,
        WEATHER,
        CRYPTO
    } DisplayMode;

    // Weather info struct
    struct WeatherInfo {
        int temp;
        int humidity;
        int pressure;
        bool isValid;
        int showing;
    };

    // Crypto info struct
    struct CryptoInfo {
        const char ticker[10]; // e.g. BTC, ETH, DOGE
        double lastValue;
        double value;
        float change;
    };

    // Global variables
    extern DisplayMode displayMode;
    extern bool newMessageReceived;
    extern char newMessage[];
    extern uint16_t datetime[];
    extern bool datetimeUpdated;
    extern WeatherInfo weatherInfo;
    extern CryptoInfo cryptoInfo[];
#endif