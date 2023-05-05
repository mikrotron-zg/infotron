/*
 * LED matrix 32x8 module 3D model
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

// LED matrix
led_matrix_width = 32.5;
led_matrix_height = 6.2;
led_matrix_offset = 5.0; // offset from PCB varies, this is mean value

// Module PCB
module_pcb_height = 1.6; // width and length are equal to LED matrix dimensions


// Headers
module_pcb_header_x = 4*led_matrix_width - 2.54;
module_pcb_header_y = led_matrix_width/2 - 12.7/2;
module_pcb_header_z = 5;

// Entry point, uncomment the line bellow to see the object
//led_matrix_32x8();

module led_matrix_32x8(){
    draw_pcb();
    translate([0, 0, module_pcb_height + led_matrix_offset]) color("White") 
        cube([4*led_matrix_width, led_matrix_width, led_matrix_height]);
    translate([module_pcb_header_x, module_pcb_header_y, module_pcb_header_z])
        rotate([90, 0, 90]) header_pin(1,5);
}

module draw_pcb(){
    color("SteelBlue") cube([4*led_matrix_width, led_matrix_width, module_pcb_height]);    
}

