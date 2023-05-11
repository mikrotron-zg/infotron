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

#ifndef WEATHER_INFO_H
    #define WEATHER_INFO_H
    #define WEATHER_API_PREFIX "https://api.openweathermap.org/data/2.5/weather?"
    // Geographical coordinates for weather info, this ones are for Zagreb, Croatia:
    #define LATITUDE 45.84
    #define LONGITUDE 15.98

    #include "Credentials.h" // please read the instructions in include/CredentialsTemplate.h file
    /**
     * @brief Gets weather info from OpenWeather API
     * 
     * Connects to OpenWeather server, downloads and parses received JSON file.
     */
    void getWeatherInfo();
#endif