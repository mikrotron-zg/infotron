/*
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * developed by Mikrotron d.o.o. (http://mikrotron.hr).
 * It contains macros and debugging variables.
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
 * If you want to turn debug mode on, place the line:
 * 
 * #define DEBUG_MODE
 * 
 * in file Configuration.h before the include call for this file, i.e.
 * #include "Debug.h".
 * 
 * If you want to turn debug mode off, comment out or delete the
 * DEBUG_MODE definition line:
 * 
 * //#define DEBUG_MODE
 *******************************************************************/

#ifndef DEBUG_H
    #define DEBUG_H
    #ifdef DEBUG_MODE // debug development settings
        #warning "WARNING! Debug mode is enabled, disable for production!"
        // calls to DEBUG will be replaced with Serial.print command
        #define DEBUG(x) Serial.print(x)
        // calls to DEBUGLN will be replaced with Serial.println command
        #define DEBUGLN(x) Serial.println(x)
    #else // production settings
        // calls to DEBUG and DEBUGLN will be replaced with nothing
        #define DEBUG(x)
        #define DEBUGLN(x)
    #endif
#endif