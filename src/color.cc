#include "color.hpp"
#include <iostream>
#include <cstdlib>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  if (red_ > kColorValueMax || red_ < kColorValueMin) {
    throw std::invalid_argument("Invalid color");
  }
  if (green_ > kColorValueMax || green_ < kColorValueMin) {
    throw std::invalid_argument("Invalid Color");
  }
  if (blue_ > kColorValueMax || blue_ < kColorValueMin) {
    throw std::invalid_argument("Invalid Color");
  }
}

int Color::Red() const {
  return red_;
}
int Color::Green() const {
  return green_;
}
int Color::Blue() const {
  return blue_;
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}