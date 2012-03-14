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

  std::cout << std::endl << std::endl << "Starting work on test.ppm" << std::endl << std::endl;

  std::ofstream outputFile;
  Image i2 = Image::readPPM("data/test.ppm");

  std::cout << "..result_smooth.ppm";
  Image i_smooth = Image(i2);
  Image::smoothen(i2, i_smooth, 0, i2.m_height);
  outputFile.open("result_smooth.ppm");
  i_smooth.printPPM(outputFile);
  outputFile << std::flush;
  outputFile.close();
  std::cout << " done!" << std::endl;

  std::cout << "..result_sharp.ppm";
  Image i_sharp = Image(i2);
  Image::sharpen(i2, i_sharp, 0, i2.m_height);
  outputFile.open("result_sharp.ppm");
  i_sharp.printPPM(outputFile);
  outputFile << std::flush;
  outputFile.close();
  std::cout << " done!" << std::endl;

  std::cout << "..result_both.ppm";
  Image i_both = Image(i_smooth);
  Image::sharpen(i_smooth, i_both, 0, i_smooth.m_height);
  outputFile.open("result_both.ppm");
  i_both.printPPM(outputFile);
  outputFile << std::flush;
  outputFile.close();
  std::cout << " done!" << std::endl;

  std::cout << std::endl << std::endl << "Notice!" << std::endl << "It will override the file if it existed" << std::endl;

  return 0;
}

