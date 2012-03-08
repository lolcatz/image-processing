#include <iostream>
#include "image.h"

int main(void) {
  Image i = Image::readPPM("data/feep.ppm");
  std::cout << "Image: " << i.height << std::endl;

  return 0;
}

