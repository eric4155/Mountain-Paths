#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
//   const std::string kTestInputFile =
//        "./example-data/ex_input_data/prompt_5w_2h.dat";
//  constexpr size_t kTestInputFileWidth = 5;
//   constexpr size_t kTestInputFileHeight = 2;

//   ElevationDataset ed(
//         kTestInputFile, kTestInputFileWidth, kTestInputFileHeight);
//   GrayscaleImage gi2(ed);
//   PathImage pi(gi2, ed);
  const std::string kStudentOutput =
      "./student_out/ex_path_image_prompt_w51-h55";
  const std::string kTestFile = "./example-data/ex_input_data/map-input-w51-h55.dat";
  const std::string kGroundTruth =
      "./example-data/ex_output_paths/map-input-w51-h55.ppm";
  constexpr size_t kTestFileWidth = 51;
  constexpr size_t kTestFileHeight = 55;
  ElevationDataset ed(kTestFile, kTestFileWidth, kTestFileHeight);
  GrayscaleImage gi(ed);
  PathImage pi(gi, ed);
  pi.ToPpm(kStudentOutput);
}

