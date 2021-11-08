// LED matrix 32x8 module model by Mikrotron d.o.o.

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

