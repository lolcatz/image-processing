#include <iostream>
#include "image.h"

int main(void) {
  Image i = Image::readPPM("data/feep.ppm");
  Image smoothened = Image(i);
  Image sharpened = Image(i);
  std::cout << "Original image:" << std::endl;
  i.printPPM(std::cout);

  std::cout << "Smoothened image:" << std::endl;
  Image::smoothen(i, smoothened, 0, i.m_height);
  smoothened.printPPM(std::cout);

  std::cout << "Sharpened image:" << std::endl;
  Image::sharpen(smoothened, sharpened, 0, smoothened.m_height);
  sharpened.printPPM(std::cout);


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

