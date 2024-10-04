#include "path_image.hpp"
#include "path.hpp"
#include <fstream>

PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& dataset) 
    : width_(dataset.Width()), height_(dataset.Height()), path_image_(image.GetImage()) {
    // Looping through rows; i represents the starting row value
    for (size_t i = 0; i < height_; ++i) {
        Path current_path = {width_, i};
        current_path.SetLoc(0, i);
        unsigned int current_row = i;
        // Looping through columns; j represents column we are in 
        for (unsigned int j = 0; j < width_ - 1; ++j) {
            int current_value = dataset.DatumAt(current_row, j);
            int forward = dataset.DatumAt(current_row, j + 1);
            int forward_down = 0;
            int forward_up = 0;
            if (current_row == 0) {
                forward_down = dataset.DatumAt(current_row + 1, j + 1);
            } else if (current_row == height_ - 1) {
                forward_up = dataset.DatumAt(current_row - 1, j + 1);
            } else {
                forward_up = dataset.DatumAt(current_row - 1, j + 1);
                forward_down = dataset.DatumAt(current_row + 1, j + 1);
            }
            if (std::abs(current_value - forward) <= std::abs(current_value - forward_down) && 
                std::abs(current_value - forward) <= std::abs(current_value - forward_up)) {
                current_path.SetLoc(j + 1, current_row);
                current_path.IncEleChange(std::abs(current_value - forward));
            } else if (std::abs(current_value - forward_down) <= std::abs(current_value - forward_up)) {
                current_path.SetLoc(j + 1, current_row + 1);
                current_path.IncEleChange(std::abs(current_value - forward_down));
                current_row++;
            } else {
                current_path.SetLoc(j + 1, current_row - 1);
                current_row--;
                current_path.IncEleChange(std::abs(current_value - forward_up));
            }
        }
        paths_.push_back(current_path);
    }
    std::cout << "completed construction of path image" << std::endl;
    CreatePathImage();
}

size_t PathImage::CalcBestPathIndex() const {
    Path best_path = paths_.at(0);
    for (unsigned int i = 1; i < paths_.size(); ++i) {
        if (paths_.at(i).EleChange() < best_path.EleChange()) {
            best_path = paths_.at(i);
        }
    }
    return best_path.StartingRow();
}

void PathImage::CreatePathImage() {
    size_t best_index = CalcBestPathIndex();
    // Loops through each path as path object
    for (unsigned int i = 0; i < paths_.size(); i++) {
        // Loops through each path as vector
        for (unsigned int j = 0; j < paths_.at(i).Length(); j++) {
            path_image_.at(paths_.at(i).GetPath().at(j)).at(j) = kRed;
        }
    }
    for (unsigned int i = 0; i < paths_.at(best_index).Length(); ++i) {
        path_image_.at(paths_.at(best_index).GetPath().at(i)).at(i) = kGreen;
    }
   // std::cout << "Path image created" << std::endl;
}
size_t PathImage::Width() const {
    return width_;
}
size_t PathImage::Height() const {
    return height_;
}
unsigned int PathImage::MaxColorValue() const {
    return kMaxColorValue;
}
const std::vector<Path>& PathImage::Paths() const {
    return paths_;
}
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
    return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
    std::ofstream output_file{name};
    if (!output_file.is_open()) {
        throw std::runtime_error("File not open");
    }
    output_file << "P3" << std::endl;
    output_file << width_ << ' ' << height_ << std::endl;
    output_file << kMaxColorValue << std::endl;
    for (unsigned int i = 0; i < path_image_.size(); ++i) {
        for (unsigned int j = 0; j < path_image_.at(i).size(); ++j) {
            Color current_color = path_image_.at(i).at(j);
            output_file << current_color.Red() << ' ' << current_color.Green() << ' ' << current_color.Blue() << ' ';
        }
        output_file << std::endl;
    }
}
