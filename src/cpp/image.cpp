#include "image.h"
#include "pixel.h"
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

  //Pixel[m_height*m_width] data;
  Pixel* data = new Pixel[m_height*m_width];
  for (unsigned int i=1; i<=m_width; i++) {
    for (unsigned int k=1; k<=m_height; k++) {
      Pixel pxl = m_data[i*k];
      bool right = false;
      bool left = false;
      //Saman rivin viereiset pikselit
      if (i+1 < m_width) {
        pxl.r += (pxl.r - m_data[(i+1)*k-1].r) * (1/7);
        pxl.g += (pxl.g - m_data[(i+1)*k-1].g) * (1/7);
        pxl.b += (pxl.b - m_data[(i+1)*k-1].b) * (1/7);
        right = true;
      }
      if (i-1 > 0)
      {
        pxl.r += (pxl.r - m_data[(i-1)*k-1].r) * (1/7);
        pxl.g += (pxl.g - m_data[(i-1)*k-1].g) * (1/7);
        pxl.b += (pxl.b - m_data[(i-1)*k-1].b) * (1/7);
        left = true;
      }
      //Yläpikselit
      if (k-1 > 0)
      {
        if (right)
        {
          pxl.r += (pxl.r - m_data[(i+1)*(k-1)-1].r) * (1/7);
          pxl.g += (pxl.g - m_data[(i+1)*(k-1)-1].g) * (1/7);
          pxl.b += (pxl.b - m_data[(i+1)*(k-1)-1].b) * (1/7);
        }

        pxl.r += (pxl.r - m_data[(i)*(k-1)-1].r) * (1/7);
        pxl.g += (pxl.g - m_data[(i)*(k-1)-1].g) * (1/7);
        pxl.b += (pxl.b - m_data[(i)*(k-1)-1].b) * (1/7);
        if (left)
        {
          pxl.r += (pxl.r - m_data[(i-1)*(k-1)-1].r) * (1/7);
          pxl.g += (pxl.g - m_data[(i-1)*(k-1)-1].g) * (1/7);
          pxl.b += (pxl.b - m_data[(i-1)*(k-1)-1].b) * (1/7);
        }
      }

      //Alapikselit
      if (k+1 < m_height)
      {
        if (right)
        {
          pxl.r += (pxl.r - m_data[(i+1)*(k+1)-1].r) * (1/7);
          pxl.g += (pxl.g - m_data[(i+1)*(k+1)-1].g) * (1/7);
          pxl.b += (pxl.b - m_data[(i+1)*(k+1)-1].b) * (1/7);
        }

        pxl.r += (pxl.r - m_data[(i)*(k+1)-1].r) * (1/7);
        pxl.g += (pxl.g - m_data[(i)*(k+1)-1].g) * (1/7);
        pxl.b += (pxl.b - m_data[(i)*(k+1)-1].b) * (1/7);

        if(left)
        {
          pxl.r += (pxl.r - m_data[(i-1)*(k+1)-1].r) * (1/7);
          pxl.g += (pxl.g - m_data[(i-1)*(k+1)-1].g) * (1/7);
          pxl.b += (pxl.b - m_data[(i-1)*(k+1)-1].b) * (1/7);
        }
      }
    }
  }
  m_data = data;
}
