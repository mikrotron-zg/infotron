#include "Configuration.h" 
#include "DateTimeHandler.h"

// Declare timer
hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer(){
    // Fires once every second
    datetime[5]++;
    datetimeUpdated = true;
}

void validateTime() {
    // Checks if time is valid, date validation not implemented!
    if (datetime[5] <  60) return; // nothing to do here
    if (datetime[5] >= 60) { // in case we miss a cycle
       datetime[5] -= 60;
       datetime[4]++;
        if (datetime[4] == 60) {
            datetime[4] = 0;
            datetime[3]++;
            if (datetime[3] == 24) {
                datetime[3] = 0;
                // TODO should update date too at this point
            }
       } 
    }
}

void startTimer() {
    // Attach timer wich fires once every second and start it
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);
    timerAlarmEnable(timer);
    datetimeUpdated = true;
}

void parseInitTime(String input) {
    // Parse date and time to datetime array
    datetime[0] = input.substring(8,10).toInt();
    datetime[1] = input.substring(5,7).toInt();
    datetime[2] = input.substring(0,4).toInt();
    datetime[3] = input.substring(11,13).toInt() + TIME_ZONE;
    // Adding time zone correction might create overflow
    if (datetime[3] > 23) datetime [3] -= 24; 
    // TODO: handle negative time zone and add date correction
    datetime[4] = input.substring(14,16).toInt();
    float sec = input.substring(17,22).toFloat() + 0.5;
    datetime[5] = (int)sec;
    validateTime();
}

void startDateTime(String initTime) {
    // Start handeling date/time
    parseInitTime(initTime);
    startTimer();
}

void stopDateTime() {
    // Disable timer and clear data
    timerAlarmDisable(timer);
    for (int i = 0; i < 6; i++) {
        datetime[i] = 0;
    }
}

