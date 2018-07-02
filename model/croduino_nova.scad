// Croduino NOVA 3D model by Mikrotron d.o.o.

include <common.scad>;

// Board dimensions
nova_length = 50.0;
nova_width = 23.75;
nova_height = 1.6;

// ESP8266 module board dimensions and position
esp_length = 24.0;
esp_width = 16.2;
esp_height = 1.0;
esp_m_length = 15.75;
esp_m_width = 12.6;
esp_m_height = 3.0;
esp_x = 57.0 - esp_length;

// Headers positions
header_x = nova_length - 26.75;
header_y = 0.5;

// Entry point, uncomment the line bellow to see the object
croduino_nova();

module croduino_nova(){
    nova_board();
    translate([esp_x, nova_width/2 - esp_width/2, nova_height]) esp_board();
}

module nova_board(){
    // Draw Croduino NOVA board
    color("SteelBlue") cube([nova_length, nova_width, nova_height]);
    // Add headers
    translate([header_x, header_y, nova_height]) header_pin(1,10);
    translate([header_x, nova_width - header_y - 2.54, nova_height]) header_pin(1,10);
}

module esp_board(){
    // Draw ESP8266 module board
    color("Teal") cube([esp_length, esp_width, esp_height]);
    // Draw ESP8266 module
    translate([1, esp_width/2 - esp_m_width/2, esp_height])
        color("Ivory") cube([esp_m_length, esp_m_width, esp_m_height]);
}