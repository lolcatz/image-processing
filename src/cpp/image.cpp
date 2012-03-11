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

Image::~Image() {
  delete[] m_data;
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

  Image img(width, height, maxval);

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
  return m_width * height + width;
}

Image Image::smoothen() {
  //cout << "Smoothing <3" << endl;
  //smaller value == stronger smoothing
  int strength = 7;
  // Smoothening. doing smoothed values into a new m_data
  //Pixel[m_height*m_width] data;
  Image img(m_width, m_height, m_maxval);
  Pixel* data = img.m_data;
  for (unsigned int k=0; k < m_height; k++) {
    for (unsigned int i=0; i < m_width; i++) {
      //cout << i << ", " << k << endl;
      Pixel pxl;
      pxl = m_data[index(k, i)];
      //cout << "doing something" << endl;
      bool right = false;
      bool left = false;
      //Saman rivin viereiset pikselit
      if (i+1 < m_width) {
        pxl.r -= (pxl.r - m_data[index(k, i+1)].r)/strength;
        pxl.g -= (pxl.g - m_data[index(k, i+1)].g)/strength;
        pxl.b -= (pxl.b - m_data[index(k, i+1)].b)/strength;
        right = true;
      }
      if ((int)i-1 >= 0)
      {
        pxl.r -= (pxl.r - m_data[index(k, i-1)].r)/strength;
        pxl.g -= (pxl.g - m_data[index(k, i-1)].g)/strength;
        pxl.b -= (pxl.b - m_data[index(k, i-1)].b)/strength;
        left = true;
      }
      //Yläpikselit
      if ((int)k-1 >= 0)
      {
        if (right)
        {
          pxl.r -= (pxl.r - m_data[index(k-1, i+1)].r)/strength;
          pxl.g -= (pxl.g - m_data[index(k-1, i+1)].g)/strength;
          pxl.b -= (pxl.b - m_data[index(k-1, i+1)].b)/strength;
        }

        pxl.r -= (pxl.r - m_data[index(k-1, i)].r)/strength;
        pxl.g -= (pxl.g - m_data[index(k-1, i)].g)/strength;
        pxl.b -= (pxl.b - m_data[index(k-1, i)].b)/strength;
        if (left)
        {
          pxl.r -= (pxl.r - m_data[index(k-1, i-1)].r)/strength;
          pxl.g -= (pxl.g - m_data[index(k-1, i-1)].g)/strength;
          pxl.b -= (pxl.b - m_data[index(k-1, i-1)].b)/strength;
        }
      }

      //Alapikselit
      if (k+1 < m_height)
      {
        if (right)
        {
          pxl.r -= (pxl.r - m_data[index(k+1, i+1)].r)/strength;
          pxl.g -= (pxl.g - m_data[index(k+1, i+1)].g)/strength;
          pxl.b -= (pxl.b - m_data[index(k+1, i+1)].b)/strength;
        }

        pxl.r -= (pxl.r - m_data[index(k+1, i)].r)/strength;
        pxl.g -= (pxl.g - m_data[index(k+1, i)].g)/strength;
        pxl.b -= (pxl.b - m_data[index(k+1, i)].b)/strength;

        if(left)
        {
          pxl.r -= (pxl.r - m_data[index(k+1, i-1)].r)/strength;
          pxl.g -= (pxl.g - m_data[index(k+1, i-1)].g)/strength;
          pxl.b -= (pxl.b - m_data[index(k+1, i-1)].b)/strength;
        }
      }
      if (pxl.r < 0)
        pxl.r = 0;
      if (pxl.b < 0)
        pxl.b = 0;
      if (pxl.g < 0)
        pxl.g = 0;

      //cout << "finished this pixel" << endl;
      data[index(k, i)] = pxl;
    }
  }
  return img;
}

Image Image::sharpen() {
  //cout << "Sharpening <3" << endl;
  int strength = 7;
  // copy&pasta

  //Pixel[m_height*m_width] data;
  Image img(m_width, m_height, m_maxval);
  Pixel* data = img.m_data;

  for (unsigned int i=0; i< m_width; i++) {
    for (unsigned int k=0; k< m_height; k++) {
      //cout << i << ", " << k << endl;
      Pixel pxl;
      pxl = m_data[index(k, i)];
      //cout << "doing something" << endl;
      bool right = false;
      bool left = false;
      //Saman rivin viereiset pikselit
      if (i+1 < m_width) {
        pxl.r -= -(pxl.r - m_data[index(k, i+1)].r)/strength;
        pxl.g -= -(pxl.g - m_data[index(k, i+1)].g)/strength;
        pxl.b -= -(pxl.b - m_data[index(k, i+1)].b)/strength;
        right = true;
      }
      if ((int)i-1 >= 0)
      {
        pxl.r -= -(pxl.r - m_data[index(k, i-1)].r)/strength;
        pxl.g -= -(pxl.g - m_data[index(k, i-1)].g)/strength;
        pxl.b -= -(pxl.b - m_data[index(k, i-1)].b)/strength;
        left = true;
      }
      //Yläpikselit
      if ((int)k-1 >= 0)
      {
        if (right)
        {
          pxl.r -= -(pxl.r - m_data[index(k-1, i+1)].r)/strength;
          pxl.g -= -(pxl.g - m_data[index(k-1, i+1)].g)/strength;
          pxl.b -= -(pxl.b - m_data[index(k-1, i+1)].b)/strength;
        }

        pxl.r -= -(pxl.r - m_data[index(k-1, i)].r)/strength;
        pxl.g -= -(pxl.g - m_data[index(k-1, i)].g)/strength;
        pxl.b -= -(pxl.b - m_data[index(k-1, i)].b)/strength;
        if (left)
        {
          pxl.r -= -(pxl.r - m_data[index(k-1, i-1)].r)/strength;
          pxl.g -= -(pxl.g - m_data[index(k-1, i-1)].g)/strength;
          pxl.b -= -(pxl.b - m_data[index(k-1, i-1)].b)/strength;
        }
      }

      //Alapikselit
      if (k+1 < m_height)
      {
        if (right)
        {
          pxl.r -= -(pxl.r - m_data[index(k+1, i+1)].r)/strength;
          pxl.g -= -(pxl.g - m_data[index(k+1, i+1)].g)/strength;
          pxl.b -= -(pxl.b - m_data[index(k+1, i+1)].b)/strength;
        }

        pxl.r -= -(pxl.r - m_data[index(k+1, i)].r)/strength;
        pxl.g -= -(pxl.g - m_data[index(k+1, i)].g)/strength;
        pxl.b -= -(pxl.b - m_data[index(k+1, i)].b)/strength;

        if(left)
        {
          pxl.r -= -(pxl.r - m_data[index(k+1, i-1)].r)/strength;
          pxl.g -= -(pxl.g - m_data[index(k+1, i-1)].g)/strength;
          pxl.b -= -(pxl.b - m_data[index(k+1, i-1)].b)/strength;
        }
      }
      if (pxl.r < 0)
        pxl.r = 0;
      if (pxl.b < 0)
        pxl.b = 0;
      if (pxl.g < 0)
        pxl.g = 0;

      //cout << "finished this pixel" << endl;
      data[index(k, i)] = pxl;
    }
  }
  return img;
}

std::ostream& Image::printPPM(std::ostream& out) {
  out << "P3" << endl;
  out << m_width << " " << m_height << endl;
  out << m_maxval << endl;
  for (unsigned int i = 0; i < m_height; i++ ) {
    for (unsigned int k = 0; k < m_width; k++ ) {
      out << m_data[index(i,k)].r << " ";
      out << m_data[index(i,k)].g << " ";
      out << m_data[index(i,k)].b << " ";
      out << "   ";
    }
    out << endl;
  }
  return out;
}
