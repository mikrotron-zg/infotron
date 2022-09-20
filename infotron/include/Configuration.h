/*******************************************************************
 * This files contains global variables, settings and includes
 * needed for multiple project modules
 *******************************************************************/

#ifndef CONFIGURATION_H
    #define CONFIGURATION_H
    // Settings
    #define DEBUG_MODE // please read the instructions in include/Debug.h file

    // Includes
    #include <SPIFFS.h>
    #include <ESPAsyncWebServer.h>
    #include "Debug.h"

    // Display mode enum
    // Enums
    typedef enum {
        TEXT,
        DATETIME,
        WEATHER
    } DisplayMode;

    // Global variables
    extern DisplayMode displayMode;
    extern bool newMessageReceived;
    extern char newMessage[];
#endif