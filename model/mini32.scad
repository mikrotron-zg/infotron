// D1 MINI 32 PCB model by Mikrotron d.o.o.

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