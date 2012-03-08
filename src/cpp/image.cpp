#include "image.h"
#include <fstream>
#include <iostream>

using namespace std;

Image::Image(unsigned width, unsigned height, unsigned maxval):
  m_width(width),
  m_height(height),
  m_maxval(maxval),
  m_data(new unsigned char[width*height])
{
}

Image Image::readPPM(const std::string& filename) {
  ifstream f(filename);
  if (f.is_open()) {
    while (f.good()) {
      string s;
      getline(f, s);
      cout << s << endl;
    }
  }

  Image i = Image(4,5,5);
  return i;
}

