#include <iostream>
#include "image.h"

int main(void) {
  Image i = Image::readPPM("data/feep.ppm");
  //std::cout << "Image: " << i.m_height << std::endl;
  //i.smoothen();
  //i.printPPM(std::cout);
  i.smoothen();
  i.printPPM(std::cout);

  return 0;
}

