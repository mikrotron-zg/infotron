// Infotron box 3D model by Mikrotron d.o.o.

include<led_matrix_32x8.scad>;
include<croduino_nova.scad>;

// Box dimensions
wall = 1.0; // box wall width
wall2 = 1.75*wall; // thicker box wall
screen_border = 2*wall + 1.0; // screen border width
box_width = led_matrix_width + 2*screen_border;
box_length = screen_border + 4*led_matrix_width + nova_length;
box_top_height = led_matrix_height + led_matrix_offset + module_pcb_height + 3; 
box_bottom_height = 9 + wall2;
box_overlap_height = 5;

// Modules inside the box
nova_raised = 2.4; // how much is nova raised from the bottom
screen_raised = box_bottom_height + 3; // how much is screen raised from the bottom

// Screen bracket clip
screen_clip_length = 5.0;
screen_clip_width = screen_border - wall2;
screen_clip_ledge = 0.6;


// Entry point
infotron_box();

module infotron_box(){
    translate([0, 1.2*box_width, 0]){
    color ("Blue") draw_top();
    translate([screen_border, screen_border + led_matrix_width, led_matrix_height + led_matrix_offset + module_pcb_height]) rotate([180, 0, 0]) #%led_matrix_32x8();
    }
//    draw_bottom();
//    translate([screen_border, screen_border, screen_raised]) #%led_matrix_32x8();
//    translate([box_length - wall2, box_width/2 + nova_width/2, nova_raised + wall2]) rotate(180) #%croduino_nova();
}

module draw_bottom(){
    bottom_shell();
    translate([screen_border, screen_border, wall2]) screen_distancers();
    screen_clips();
    nova_mount();
}

module nova_mount(){
    groove = 0.5;
    translate([box_length - nova_length - wall2, box_width/2 - nova_width/2 - wall2 + groove, wall2]){
        difference(){
            cube([nova_length, wall2, nova_raised + nova_height + 2]);
            translate([0, wall2 - groove, nova_raised])
                cube([nova_length, groove + ex, nova_height + 0.4]);
        }
        translate([-wall2, 0, 0]) cube([wall2, wall2 + 2, nova_raised + nova_height]);
        translate([0, nova_width + groove, 0]){
            difference(){
            cube([nova_length, wall2, nova_raised + nova_height + 2]);
            translate([0, -ex, nova_raised])
                cube([nova_length, groove + ex, nova_height + 0.4]);
            }
            translate([-wall2, -2, 0]) cube([wall2, wall2 + 2, nova_raised + nova_height]);
        }
    }
}

module screen_clips(){
    clip_x1 = screen_border + module_pcb_hole_pos[0][0];
    clip_x2 = screen_border + module_pcb_hole_pos[1][0];
    clip_y = box_width - wall2;
    
    translate([clip_x1, wall2, wall2]) screen_clip();
    translate([clip_x2, wall2, wall2]) screen_clip();
    translate([clip_x1, clip_y, wall2]) rotate(180) screen_clip();
    translate([clip_x2, clip_y, wall2]) rotate(180) screen_clip();
}

module screen_distancers(){
    for(i = [0 : 3]){
            translate(module_pcb_hole_pos[i]){
                cylinder(r1 = 3.5, r2 = 2.5, h = screen_raised - wall2, $fn=25);
                translate([0, 0, screen_raised - wall2]) 
                    cylinder(d = 3, h = module_pcb_height + 1, $fn=25);
            }
    }
}

module bottom_shell(){
    difference(){
        rounded_rect(box_length, box_width, box_bottom_height);
        translate([wall2, wall2, wall2])
            cube([box_length - 2*wall2, box_width - 2*wall2, box_bottom_height - wall2 + ex]);
        translate([box_length - wall2 - ex, box_width/2 - usb_length/2 - 0.5, nova_raised + wall2 + nova_height - 0.5])
            cube([wall2 + 2*ex, usb_length + 1, usb_height + 1]);
    }
    translate([wall, wall, box_bottom_height]) difference(){
        cube([box_length - 2*wall, box_width - 2*wall, box_overlap_height]);
        translate([wall2 - wall, wall2 - wall, -ex])
            cube([box_length - 2*wall2, box_width - 2*wall2, box_overlap_height + 2*ex]);
    }
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
        translate([screen_border, screen_border, 0.3])
            cube([4*led_matrix_width, led_matrix_width, wall + 2*ex]);
        translate([box_length - nova_length/2, box_width - screen_border, -ex]) top_text();
    }
}

module screen_bracket(bracket_height = 3){
    // Draw bracket
    difference(){
        cube([4*led_matrix_width + 2*wall, led_matrix_width + 2*wall, bracket_height]);
        translate([wall, wall, -ex])
            cube([4*led_matrix_width, led_matrix_width, led_matrix_width + 2*ex]);
    }
}

module screen_clip(){
    translate([-screen_clip_length/2, 0, 0]){
        cube([screen_clip_length, screen_clip_width, screen_raised - wall2 + module_pcb_height + screen_clip_ledge]);
        translate([0, screen_clip_width, screen_raised - wall2 + module_pcb_height + screen_clip_ledge]) rotate([0, 90, 0])
            linear_extrude(height = screen_clip_length) polygon([[0, 0], [screen_clip_ledge, 0], [0, screen_clip_ledge]]);
    }
}

module top_text(){
    rotate([180, 0, 0]) translate([0, 0, -0.3]) linear_extrude(height = 0.3)
        text("infotron", size = 8, font = "Liberation Sans", halign = "center",                valign = "bottom");
}