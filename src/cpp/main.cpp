#include <iostream>
#include "image.h"

int main(void) {
  Image i = Image::readPPM("data/feep.ppm");
  std::cout << "Original image:" << std::endl;
  i.printPPM(std::cout);

  std::cout << "Smoothened image:" << std::endl;
  Image i2 = i.smoothen();
  i2.printPPM(std::cout);

  std::cout << "Sharpened image:" << std::endl;
  Image i3 = i2.sharpen();
  i3.printPPM(std::cout);

  return 0;
}

