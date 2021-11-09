// Infotron box 3D model by Mikrotron d.o.o.

include<led_matrix_32x8.scad>;
include<mini32.scad>;


// Box dimensions
wall = 1.6; // box wall width
wall2 = 1.25*wall; // thicker box wall
screen_border = 2*wall + 3.0; // screen border width
box_width = led_matrix_width + 2*screen_border;
box_length = screen_border + 4*led_matrix_width + 50;
box_top_height = led_matrix_height + led_matrix_offset + module_pcb_height + wall + 0.4; 
box_bottom_height = 8 + wall2;
box_overlap_height = 5;
slit_height = 1.5;
slit_width = wall/2;

// ESP32 mount dimensions
esp32_mount_width = 6;
esp32_mount_height = box_top_height - wall2;
esp32_mount_offset = 1;
esp32_mount_corner = esp32_mount_width - esp32_mount_offset;

// Entry point
infotron_box();

module infotron_box(){
    // Draws bottom and top part of the box, comment out one or the other for single object
    draw_bottom();
    translate([0, 1.2*box_width, 0]) draw_top();
}

module draw_bottom() {
    color ("White") difference() {
        union(){
            bottom_shell();
            // Overlap wall
            translate([wall, wall, wall2]) overlap();
            translate([box_length, box_width/2 - mini32_width/2, wall2]) 
                esp32_fixers();
            translate([screen_border + led_matrix_width/2 - esp32_mount_width/2,
                        box_width/2 - esp32_mount_width/2, wall2])
                led_matrix_fixers();
        }
        // USB cutout
        translate([box_length - 2*wall - ex, 
                   box_width/2 - mini32_usb_width/2 - 1,
                   box_bottom_height - mini32_usb_height - 1])
            cube([3*wall, mini32_usb_width + 2, mini32_usb_height + 1 + ex]);
        // Removing corners
        translate([0, 0, box_bottom_height]) 
            cube([4*wall, 4*wall, box_overlap_height + ex]);
        translate([0, box_width - 4*wall, box_bottom_height]) 
            cube([4*wall, 4*wall, box_overlap_height + ex]);
    }
}

module bottom_shell() {
    difference(){
        rounded_rect(box_length, box_width, box_bottom_height);
        translate([wall, wall, wall2])
             cube([box_length - 2*wall, box_width - 2*wall, 
                    box_bottom_height - wall2 + ex]);
    }
}

module overlap() {
    inner_wall_height = box_bottom_height - wall2;
    difference() {
        cube([box_length - 2*wall, box_width - 2*wall, 
                inner_wall_height + box_overlap_height]);
        translate([wall, wall, -ex])
            cube([box_length - 2*wall, box_width - 4*wall,
                   inner_wall_height + box_overlap_height + 2*ex]);
    }
    translate([0, 0, inner_wall_height + box_overlap_height - 0.75*slit_height]) clips();
}

module clips() {
    clip_length = 5;
    translate([0, box_width/2 - wall - clip_length/2, 0])
        rotate(90) clip(clip_length);
    for (i = [1 : 5]) {
        translate([i*(box_length - 2*wall)/6, -slit_width, 0]) clip(clip_length);
        translate([i*(box_length - 2*wall)/6, box_width - 2*wall, 0]) 
            clip(clip_length);
    }
}

module clip(length) {
    cube([length, slit_width, 0.75*slit_height]);
}

module draw_top(){
    color ("White") {
        top_shell();
        translate([screen_border - wall, screen_border - wall, wall]) screen_bracket();
        translate([box_length - wall, box_width/2 + mini32_width/2, wall2])
            rotate(180) esp32_mount();
    }
    translate([screen_border, screen_border + led_matrix_width, led_matrix_height + led_matrix_offset + module_pcb_height]) 
            rotate([180, 0, 0]) %led_matrix_32x8();
    translate([box_length - wall, box_width/2 + mini32_width/2, box_top_height - mini32_height])
            rotate(180) %mini32();
}

module top_shell(){
    difference(){
        rounded_rect(box_length, box_width, box_top_height);
        translate([wall, wall, wall2])
            cube([box_length - 2*wall, box_width - 2*wall, box_top_height - wall2 + ex]);
        // Slit
        translate([slit_width, slit_width, box_top_height - box_overlap_height])
            cube([box_length - 2*slit_width, box_width - 2*slit_width, slit_height]);
        // Screen diffuser
        translate([screen_border, screen_border, 0.4])
            cube([4*led_matrix_width, led_matrix_width, wall2 + 2*ex]);
        // Engraved text
        translate([box_length - 50/2, box_width - screen_border, -ex]) top_text();
    }
}

module screen_bracket(bracket_height = 4){
    // Draw bracket
    difference(){
        cube([4*led_matrix_width + 2*wall, led_matrix_width + 2*wall, bracket_height]);
        translate([wall, wall, -ex])
            cube([4*led_matrix_width, led_matrix_width, led_matrix_width + 2*ex]);
    }
}

module top_text(){
    rotate([180, 0, 0]) translate([0, 0, -0.6]) linear_extrude(height = 0.6)
        text("infotron", size = 8, font = "Liberation Sans", halign = "center",                valign = "bottom");
}

module esp32_mount() {
    translate([mini32_length - esp32_mount_corner, -esp32_mount_offset, 0])
        esp32_pillar_mount();
    translate([mini32_length + esp32_mount_offset, mini32_width - esp32_mount_corner, 0])
        rotate(90) esp32_pillar_mount();
    translate([0, -esp32_mount_offset, 0]) difference() {
        cube([esp32_mount_corner, mini32_width - mini32_reset_width + 2*esp32_mount_offset, esp32_mount_height]);
        translate([0, esp32_mount_offset, esp32_mount_height - mini32_height])
            cube([esp32_mount_corner, mini32_width - mini32_reset_width, mini32_height + ex]);
    }
}

module esp32_pillar_mount() {
    difference() {
        cube([esp32_mount_width, esp32_mount_width, esp32_mount_height]);
        translate([0, 1, esp32_mount_height - mini32_height])
            cube([esp32_mount_corner, esp32_mount_corner, mini32_height + ex]);
    }
}

module esp32_fixers() {
    translate([-mini32_length - esp32_mount_offset, -esp32_mount_offset, 0])
        cube([esp32_mount_width, esp32_mount_width, box_bottom_height - wall2]);
    translate([-mini32_length - esp32_mount_offset, 
                mini32_width - esp32_mount_width + esp32_mount_offset, 0])
        cube([esp32_mount_width, esp32_mount_width, box_bottom_height - wall2]);
}

module led_matrix_fixers() {
    for (i = [0 : 3]) {
        translate([i*led_matrix_width, 0, 0])
            cube([esp32_mount_width, esp32_mount_width, box_bottom_height - wall2]);
    }
}