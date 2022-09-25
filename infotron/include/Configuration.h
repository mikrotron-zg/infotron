/*******************************************************************
 * This files contains global variables, settings and includes
 * needed for multiple project modules
 *******************************************************************/

#ifndef CONFIGURATION_H
    #define CONFIGURATION_H
    // Settings
    #define DEBUG_MODE // comment out for production, read the instructions in include/Debug.h file
    #define MAX_SCREEN_TIME 5000 // in miliseconds

    // Includes
    #include <SPIFFS.h>
    #include <ESPAsyncWebServer.h>
    #include "Debug.h"

    // Display mode enum
    typedef enum {
        TEXT,
        DATETIME,
        WEATHER
    } DisplayMode;

    // Weather info struct
    struct WeatherInfo {
        int temp;
        int humidity;
        int pressure;
        bool isValid;
        int showing;
    };

    // Global variables
    extern DisplayMode displayMode;
    extern bool newMessageReceived;
    extern char newMessage[];
    extern uint16_t datetime[];
    extern bool datetimeUpdated;
    extern WeatherInfo weatherInfo;
#endif