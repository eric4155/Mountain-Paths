#include "elevation_dataset.hpp"
#include <fstream>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
    int counter = 0;
    CheckDim();
    for (unsigned int i = 0; i < height_; ++i) {
        std::vector<int> temp(width_);
        data_.push_back(temp);
    }
    std::ifstream elevation_file{filename};
    if (!elevation_file.is_open()) {
        throw std::runtime_error("File is not open");
    }
    int data_point = 0;
    for (unsigned int i = 0; i < data_.size(); ++i) {
        for (unsigned int j = 0; j < data_.at(i).size(); ++j) {
            elevation_file >> data_point;
            if (elevation_file.fail()) {
                throw std::runtime_error("Wrong type for elevation point");
            }
            ++counter;
            data_.at(i).at(j) = data_point;
        }
    }
    // I check for points here // If it fails, that means we have no more points to read, if it doesn't fail, 
    // that means we have read in a point that is excessive
    elevation_file >> data_point;
    if (!elevation_file.fail()) {
        throw std::runtime_error("Too many points");
    }
    if (counter != static_cast<int>(width_) * static_cast<int>(height_)) {
        throw std::runtime_error("Data does not match");
    }
    max_ele_ = CalcMax();
    min_ele_ = CalcMin();
}

void ElevationDataset::CheckDim() const {
    if (width_ < 0 || height_ < 0) {
        throw std::runtime_error("Invalid dimensions");
    }
}

int ElevationDataset::CalcMax() {
    int max = data_.at(0).at(0);
    for (unsigned int i = 0; i < data_.size(); ++i) {
        for (unsigned int j = 0; j < data_.at(i).size(); ++j) {
            if (data_.at(i).at(j) > max) {
                max = data_.at(i).at(j);
            }
        }
    }
    return max;
}

int ElevationDataset::CalcMin() {
    int min = data_.at(0).at(0);
    for (unsigned int i = 0; i < data_.size(); ++i) {
        for (unsigned int j = 0; j < data_.at(i).size(); ++j) {
            if (data_.at(i).at(j) < min) {
                min = data_.at(i).at(j);
            }
        }
    }
    return min;
}
size_t ElevationDataset::Width() const {
    return width_;
}
size_t ElevationDataset::Height() const {
    return height_;
}

int ElevationDataset::MinEle() const {
    return min_ele_;
}
int ElevationDataset::MaxEle() const {
    return max_ele_;
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
    return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
    return data_;
}
