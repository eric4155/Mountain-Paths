#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;
  void CreatePathImage(); // I created this
  size_t CalcBestPathIndex() const; // And this

private:
  std::vector<Path> paths_;
  const Color kGreen = Color(31, 253, 13); // And this
  const Color kRed = Color(252, 25, 63); // Also added this
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};

#endif