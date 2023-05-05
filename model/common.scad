/*
 * A library of common modules, functions and variables
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

// Extra dimension to remove ambiguity of walls
ex = 0.001;

// Hole dimension correction - if 3D printed holes turn out too small,
// increase the value (e.g. 1.1 = 110%), or reduce the value (e.g. 0.9 = 90%).
// Default value is 1.0 (100%)
hdc = 1.1;

// Some nuts and bolts dimensions
m3_bolt_head_dia = 6*hdc;
m3_bolt_head_height = 2;
m3_dia = 3*hdc;


module rounded_rect(x, y, z, radius = 1) {
    // Draws a rounded rectangle
    translate([radius,radius,0]) //move origin to outer limits
	linear_extrude(height=z)
		minkowski() {
			square([x-2*radius,y-2*radius]); //keep outer dimensions given by x and y
			circle(r = radius, $fn=100);
		}
}


module cylinder_quarter(r, h){
    // Draws quarter of a cylinder
    difference(){
        cylinder(r=r, h=h);
        translate ([-r-ex, -r-ex, -ex]) cube([2*r + 2*ex, r + ex, h + 2*ex]);
        translate ([-r-ex, -ex, -ex]) cube([r + ex, r + ex, h + 2*ex]);
    }
}


module header_pin(rows=1, columns=1){
    // Draws 2.54 mm male header pins
    base_width = 2.54;
    base_height = 2.54;
    header_width = 0.508;
    header_height = 5.08;
    trans = base_width/2 - header_width/2;

    for (i = [0: rows - 1]){
        for (j = [0: columns -1]){
            translate([j*base_width, i*base_width, 0]){
                color("Black") cube([base_width, base_width, base_height]);
                translate([trans , trans, base_height])
                    color("Khaki") cube([header_width, header_width, header_height]);
            }
        }
    }

}

module m3_bolt(length = 10){
    // M3 bolt mockup
    union(){
        cylinder(d = m3_dia, h = length);
        translate([0, 0, length - ex - m3_bolt_head_height]) 
            cylinder(d = m3_bolt_head_dia, h = m3_bolt_head_height + ex);
    }
}

module m3_nut_trap(){
    // Makes M3 nut trap inset
    cylinder(r=5.5/2/cos(180/6)*hdc, h=2, $fn=6);
}


