/*
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * developed by Mikrotron d.o.o. (http://mikrotron.hr).
 * It contains template for Credentials.h needed for this program to
 * compile and run. To create Credentials.h file, please follow the
 * instructions below.
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

/*********************   INSTRUCTIONS   ***************************
 * IMPORTANT! Please follow the instructions in this file before
 * you try to compile the project for the first time. This file
 * is just a template, don't change the contents of this file.
 * 
 * You need to do the following:
 * 1. Save this file as Credentials.h in include/ directory and
 *    than close this file
 * 2. Open Credentials.h file and enter new SSID and PASS for 
 *    Infotron device - you'll use this to connect directly to 
 *    Infotron, even when there is no WiFi network you can use
 * 3. Open Credentials.h file and enter your WiFi credentials under
 *    WIFI_SSID and WIFI_PASS
 *    (you can add alternate credentials or leave them commented out)
 * 
 * Credentials.h is ignored by Git (check the contents of .gitignore
 * file to confirm), so this way your credentials will be kept in
 * your local version of the project. This way you can change the 
 * project and publish your changes on Github, Gitlab, Bitbucket or
 * your own Git server without leaking sensitive information.
 *******************************************************************/

#ifndef CREDENTIALS_H
    #define CREDENTIALS_H
    // Replace with actual SSID and password for Infotron device 
    // (choose anything you want):
    #define INFOTRON_SSID "Infotron SSID here"
    #define INFOTRON_PASS "Infotron AP password here"

    // Replace with actual SSID and password for you WLAN:
    #define WIFI_SSID "WiFi SSID here"
    #define WIFI_PASS "WiFi password here"

    // If you can use alternate network in case the first one is
    // unreachable, uncomment lines bellow and enter credentials
    //#define ALTERNATE_WIFI_SSID "Alternate WiFi SSID here"
    //#define ALTERNATE_WIFI_PASS "Alternate WiFi password here"

    // API keys - any API key you need to retrieve data, we're 
    // using openweathermap.org API key here:
    #define WEATHER_API_KEY ""
#endif