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

  /*
  Image i4 = Image::readPPM("data/test.ppm");
  std::cout << "Output to file... " << std::endl;
  Image i5 = i4.smoothen();
  std::ofstream outputFile;
  outputFile.open("result_smoothened.ppm");
  i5.printPPM(outputFile);
  std::cout << "..result_smoothened.ppm done" << std::endl;

  Image i6 = Image::readPPM("data/test.ppm");
  Image i8 = i6.sharpen();
  outputFile.open("result_sharpened.ppm");
  i8.printPPM(outputfile);
  std::cout << "..result_sharpened.ppm done" << std::endl;

  Image i7 = i5.sharpen();
  outputFile.open("result_smooth_then_sharp.ppm");
  i7.printPPM(outputFile);
  std::cout << "..result_smooth&sharp.ppm done" << std::endl;

  std::cout << std::endl << std::endl << "Notice!" << std::endl << "It will not override the file if it existed" << std::endl;
  */
  return 0;
}

