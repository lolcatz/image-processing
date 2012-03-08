#include "image.h"
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

Image::Image(unsigned width, unsigned height, unsigned maxval):
  m_width(width),
  m_height(height),
  m_maxval(maxval),
  m_data(new unsigned char[width*height])
{
}

Image Image::readPPM(const std::string& filename) {
  unsigned height;
  unsigned width;
  unsigned maxval;

  ifstream f(filename);
  if (f.is_open()) {
    string s;
    getline(f, s);
    assert(s == "P3");
    f >> width;
    f >> height;
    f >> maxval;

    cout << "width: " << width << endl;
    cout << "height: " << height << endl;
    cout << "maxval: " << maxval << endl;
  }

  Image i = Image(4,5,5);
  return i;
}

void Image::smoothen() {
  cout << "Smoothing <3" << endl;

  // Smoothening. doing smoothed values into a new m_data
  //char[m_height*m_width] data;
  //for (int i=0; i<m_width ; i++) {
  //  for (int k=0; k<m_height; k++) {



}
