#include "grayscale_image.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) : width_(dataset.Width()), height_(dataset.Height()) {
    // Check for valid widths and height
    if (width_ < 0 || height_ < 0) {
        throw std::runtime_error("Invalid height or width");
    }
    // First loop iterates through each vector stored in the vector
    for (unsigned int i = 0; i < dataset.GetData().size(); ++i) {
        // Declare variable for numerator of color calculation
        double numerator = dataset.GetData().at(i).at(0) - dataset.MinEle();

        // Decalre variable for denominator of color calc
        double denominator = dataset.MaxEle() - dataset.MinEle();

        int color_value = 0;

        if (denominator != 0.0) {
            color_value = static_cast<int>(std::round(numerator * kMaxColorValue / denominator));
        }

        // Calculate color value 

        // Create new color object
        Color temp_color = { color_value, color_value, color_value };

        // Create new vector of colors that holds the color object
        std::vector<Color> color_vec = { temp_color };

        for (unsigned int j = 1; j < dataset.GetData().at(i).size(); ++j) {
            numerator = dataset.GetData().at(i).at(j) - dataset.MinEle();
            if (denominator != 0.0) {
                color_value = static_cast<int>(std::round(numerator * kMaxColorValue / denominator));
            } 
            // Calculate color value 
    
            // Create new color object
            Color new_color = { color_value, color_value, color_value };
            color_vec.push_back(new_color);
        }
        image_.push_back(color_vec);
    }
}
// Finish
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) : width_(), height_(height) {
    if (width_ < 0 || height_ < 0) {
        throw std::runtime_error("Invalid height or width");
    }
    // Create dataset object
    ElevationDataset dataset(filename, width, height);
    new(this) GrayscaleImage(dataset);
    
}

size_t GrayscaleImage::Width() const {
    return width_;
}
size_t GrayscaleImage::Height() const {
    return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
    return image_;
}

// FINISH WRITING TO PPM FUNCTION
void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream output_file{name};
    output_file << "P3" << std::endl;
    output_file << width_ << ' ' << height_ << std::endl;
    output_file << kMaxColorValue << std::endl;
    for (unsigned int i = 0; i < image_.size(); ++i) {
        for (unsigned int j = 0; j < image_.at(i).size(); ++j) {
            Color current_color = image_.at(i).at(j);
            output_file << current_color.Red() << ' ' << current_color.Green() << ' ' << current_color.Blue() << ' ';
        }
        output_file << std::endl;
    }

}



