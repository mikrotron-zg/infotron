/*
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * developed by Mikrotron d.o.o. (http://mikrotron.hr).
 * It contains basic web server HTTP handling, needs files from data 
 * directory to be uploaded to ESP32 SPIFFS in order to work properly.
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

#ifndef WEBSERVER_H
    #define WEBSERVER_H
    #define HTTP_PORT         80    // web server will listen for HTTP requests on port 80

    #include "Credentials.h" // please read the instructions in include/CredentialsTemplate.h file

    /**
     * @brief Starts web server.
     * 
     * Handles basic HTTP requests on port defined by HTTP_PORT constant.
     */
    void startWebServer();
    /**
     * @brief Starts WiFi in station (STA) mode.
     * 
     * @returns True if successfully started or already running,
     *          false if not started.
     */    
    bool startWiFiStation();
#endif