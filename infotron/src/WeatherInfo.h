/*******************************************************************
 * Weather info handler, 
 *******************************************************************/

#ifndef WEATHER_INFO_H
    #define WEATHER_INFO_H
    #define WEATHER_API_PREFIX "https://api.openweathermap.org/data/2.5/weather?"
    // Geographical coordinates for weather info, this ones are for Zagreb, Croatia:
    #define LATITUDE 45.84
    #define LONGITUDE 15.98

    #include "Credentials.h" // please read the instructions in include/CredentialsTemplate.h file
    // Public functions
    void getWeatherInfo();
#endif