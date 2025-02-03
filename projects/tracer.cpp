#include <limits>
#include <cmath>
#include <iostream>
#include <fstream> 
#include <vector> 
#include "geometry.h"



void render() {
    //  Define image dimensions
    const int width = 1024;    // The width of the image (in pixels)
    const int height = 769;    // The height of the image (in pixels)
    
    //  Initialize framebuffer (a vector of Vec3f to store pixel color values)
    std::vector<Vec3f> framebuffer(width * height);  // Create a vector with width*height elements
    
    // Step 3: Fill framebuffer with pixel values (set colors based on normalized position)
    for (size_t j = 0; j < height; j++) {  
        for (size_t i = 0; i < width; i++) {  
            // Set the pixel color at position (i + j * width) in the framebuffer
            framebuffer[i + j * width] = Vec3f(j / float(height), i / float(width), 0); 
            // This assigns a color where:
            // Red = j / height (vertical normalized value)
            // Green = i / width (horizontal normalized value)
            // Blue = 0 (no blue in this case)
        }
    }

    //  Open file for writing
    std::ofstream ofs;  // Declare output file stream
    ofs.open("./out.ppm");  // Open the file "out.ppm" for writing

    //  Write PPM header
    ofs << "P6\n";  // PPM magic number for binary format
    ofs << width << " " << height << "\n";  // Write image dimensions (width height)
    ofs << "255\n";  // Maximum color value (indicating 8-bit color)

    //  Write pixel data to the file
    for (size_t i = 0; i < height * width; ++i) {  // Loop over all pixels
        for (size_t j = 0; j < 3; j++) {  // Loop over the 3 color channels (RGB)
            // Write each channel's value, clamping it between 0 and 255
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
            // We clamp each color channel value to ensure it stays between 0 and 1
            // and then multiply by 255 to convert to a valid 8-bit color value (0-255).
        }
    }

    //  Close the file
    ofs.close();  // Close the output file stream
}

int main() {
    render();  // Call the render function to generate and save the image
    return 0;  // Return 0 to indicate the program finished successfully
}
