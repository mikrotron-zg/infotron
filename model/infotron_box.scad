// Infotron box 3D model by Mikrotron d.o.o.

include<led_matrix_32x8.scad>;
include<croduino_nova.scad>;

// Box dimensions
wall = 1.0; // box wall width
screen_border = 2*wall + 1.0; // screen border width
elements_overlap = nova_length/4; // how much do the LED matrix and Nova overlap
box_width = led_matrix_width + 2*screen_border;
box_length = screen_border + 4*led_matrix_width + nova_length - elements_overlap;
box_top_height = led_matrix_height + led_matrix_offset + module_pcb_height; // same as LED matrix module

// Screen bracket clip
screen_bracket_clip_length = 4.0;
screen_bracket_clip_ledge = 0.6;

// Entry point
infotron_box();

module infotron_box(){
    color ("Blue") draw_top();
    translate([screen_border, screen_border + led_matrix_width, led_matrix_height + led_matrix_offset + module_pcb_height]) rotate([180, 0, 0]) %led_matrix_32x8();
    //draw_bottom();
}

module draw_top(){
    top_shell();
    translate([screen_border - wall, screen_border - wall, wall]) screen_bracket();
    
}

module top_shell(){
    difference(){
        rounded_rect(box_length, box_width, box_top_height);
        translate([wall, wall, wall])
            cube([box_length - 2*wall, box_width - 2*wall, box_top_height - wall + ex]);
        translate([screen_border, screen_border, -ex])
            cube([4*led_matrix_width, led_matrix_width, wall + 2*ex]);
    }
}

module screen_bracket(bracket_height = 2){
    // Draw bracket
    difference(){
        cube([4*led_matrix_width + 2*wall, led_matrix_width + 2*wall, bracket_height]);
        translate([wall, wall, -ex])
            cube([4*led_matrix_width, led_matrix_width, led_matrix_width + 2*ex]);
    }
    // Draw clips
    dx = 3*led_matrix_width/4;
    translate([0, led_matrix_width/2, 0]) rotate(-90) screen_bracket_clip();
    translate([dx, 0, 0]) screen_bracket_clip();
    translate([dx, led_matrix_width + 2*wall, 0]) rotate(180) screen_bracket_clip();
    translate([4*led_matrix_width - dx, 0, 0]) screen_bracket_clip();
    translate([4*led_matrix_width - dx, led_matrix_width + 2*wall, 0]) 
        rotate(180) screen_bracket_clip();
    
}

module screen_bracket_clip(){
    translate([-screen_bracket_clip_length/2, 0, 0]){
        cube([screen_bracket_clip_length, wall, led_matrix_height - wall]);
        translate([0, 0, led_matrix_height - wall])
            cube([screen_bracket_clip_length, wall + screen_bracket_clip_ledge, wall]);
    }
}