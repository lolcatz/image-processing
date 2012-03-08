#include "image.h"
#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

Image::Image(unsigned width, unsigned height, unsigned maxval):
  m_width(width),
  m_height(height),
  m_maxval(maxval),
  m_data(new Pixel[width*height])
{
}

Image Image::readPPM(const std::string& filename) {
  unsigned height;
  unsigned width;
  unsigned maxval;

  ifstream f(filename);
  assert(f.is_open());

  string s;
  getline(f, s);
  assert(s == "P3");

  f >> width;
  f >> height;
  f >> maxval;

  Image img(height, width, maxval);

  for (unsigned i = 0; i < height; ++i) {
    for (unsigned j = 0; j < width; ++j) {
      unsigned index = img.index(i,j);
      f >> img.m_data[index].r;
      f >> img.m_data[index].g;
      f >> img.m_data[index].b;
    }
  }

  return img;
}

unsigned Image::index(unsigned height, unsigned width) {
  return m_height * height + width;
}

void Image::smoothen() {
  cout << "Smoothing <3" << endl;

  // Smoothening. doing smoothed values into a new m_data
  //char[m_height*m_width] data;
  //for (int i=0; i<m_width ; i++) {
  //  for (int k=0; k<m_height; k++) {
}

