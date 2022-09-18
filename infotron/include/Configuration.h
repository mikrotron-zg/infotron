/*******************************************************************
 * This files contains global variables, settings and includes
 * needed for multiple project modules
 *******************************************************************/

#ifndef CONFIGURATION_H
    #define CONFIGURATION_H
    // Settings
    #define DEBUG_MODE // please read the instructions in include/Debug.h file
    #define DELAY_LONG 5000 // in miliseconds
    #define DELAY_SHORT 250 // in miliseconds

    // Pin connections
    #define STEPPER_STEP_PIN 15
    #define STEPPER_ENABLE_PIN 21
    #define STEPPER_DIR_PIN 22

    // Includes
    #include <SPIFFS.h>
    #include <ESPAsyncWebServer.h>
    #include "FastAccelStepper.h"
    #include "Debug.h"

    // Enums
    typedef enum {
        NOT_INITIALIZED,
        INITIALIZING,
        IDLE,
        RUNNING
    } Status;

    extern Status slider_status;
    extern FastAccelStepperEngine engine;
    extern FastAccelStepper *stepper;
#endif