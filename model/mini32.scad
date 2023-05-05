/*
 * D1 MINI 32 PCB 3D model
 * This file is part of Infotron project (https://github.com/mikrotron-zg/infotron)
 * by Mikrotron d.o.o. (http://mikrotron.hr)
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

include <common.scad>;

mini32_length = 39.5;
mini32_width = 32.0;
mini32_height = 1.6;
mini32_reset_width = 3.0;
mini32_reset_length = 5.0;
mini32_usb_width = 8;
mini32_usb_height = 2.4;


// Entry point, uncomment the line bellow to see the object
// mini32();

module mini32() {
    // PCB
    color("SteelBlue") difference() {
        cube([mini32_length, mini32_width, mini32_height]);
        translate([-ex, mini32_width - mini32_reset_width, -ex])
            cube([mini32_reset_length, mini32_reset_width + ex, mini32_height + 2*ex]);
    }
    // Micro USB
    translate([0, mini32_width/2 - mini32_usb_width/2, mini32_height])
        color("Gainsboro") cube([7, mini32_usb_width, mini32_usb_height]);
    // ESP32 module
    esp32();
}

module esp32() {
    pcb_width = 18.0;
    pcb_length = 26.0;
    pcb_height = 0.7;
    module_width = 16.0;
    module_length = 17.8;
    module_height = 2.4;
    module_offset = 1.0;
    
    translate([mini32_length - pcb_length, mini32_width/2 - pcb_width/2, mini32_height]) {
        color("DarkSlateGray") cube([pcb_length, pcb_width, pcb_height]);
        translate([module_offset, module_offset, pcb_height])
            color("Silver") cube([module_length, module_width, module_height]);
    }
}