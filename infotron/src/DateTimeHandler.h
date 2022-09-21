/*******************************************************************
 * Basic date/time handler, for demo purposes only
 *******************************************************************/

#ifndef DATETIMEHANDLER_H
    #define DATETIMEHANDLER_H
    #define TIMER_PRESCALER   80  // for 80 MHz this sets timer to 1 microsecond tick
    #define TIMER_TICK   1000000  // in usec, equals 1 second
    #define TIME_ZONE    2        // needed to convert form GMT (not handling daytime saving!)

    // Public functions
    void startDateTime(String initTime);
    void stopDateTime();
#endif