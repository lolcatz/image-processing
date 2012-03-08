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
  //cout << "Smoothing <3" << endl;
  //smaller value == stronger smoothing
  int strength = 30;
  // Smoothening. doing smoothed values into a new m_data
  //Pixel[m_height*m_width] data;
  Pixel* data = new Pixel[m_height*m_width];
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
        pxl.r += (pxl.r - m_data[index(k, i+1)].r) * (1/strength);
        pxl.g += (pxl.g - m_data[index(k, i+1)].g) * (1/strength);
        pxl.b += (pxl.b - m_data[index(k, i+1)].b) * (1/strength);
        right = true;
      }
      if ((int)i-1 >= 0)
      {
        pxl.r += (pxl.r - m_data[index(k, i-1)].r) * (1/strength);
        pxl.g += (pxl.g - m_data[index(k, i-1)].g) * (1/strength);
        pxl.b += (pxl.b - m_data[index(k, i-1)].b) * (1/strength);
        left = true;
      }
      //Yläpikselit
      if ((int)k-1 >= 0)
      {
        if (right)
        {
          pxl.r += (pxl.r - m_data[index(k-1, i+1)].r) * (1/strength);
          pxl.g += (pxl.g - m_data[index(k-1, i+1)].g) * (1/strength);
          pxl.b += (pxl.b - m_data[index(k-1, i+1)].b) * (1/strength);
        }

        pxl.r += (pxl.r - m_data[index(k-1, i)].r) * (1/strength);
        pxl.g += (pxl.g - m_data[index(k-1, i)].g) * (1/strength);
        pxl.b += (pxl.b - m_data[index(k-1, i)].b) * (1/strength);
        if (left)
        {
          pxl.r += (pxl.r - m_data[index(k-1, i-1)].r) * (1/strength);
          pxl.g += (pxl.g - m_data[index(k-1, i-1)].g) * (1/strength);
          pxl.b += (pxl.b - m_data[index(k-1, i-1)].b) * (1/strength);
        }
      }

      //Alapikselit
      if (k+1 < m_height)
      {
        if (right)
        {
          pxl.r += (pxl.r - m_data[index(k+1, i+1)].r) * (1/strength);
          pxl.g += (pxl.g - m_data[index(k+1, i+1)].g) * (1/strength);
          pxl.b += (pxl.b - m_data[index(k+1, i+1)].b) * (1/strength);
        }

        pxl.r += (pxl.r - m_data[index(k+1, i)].r) * (1/strength);
        pxl.g += (pxl.g - m_data[index(k+1, i)].g) * (1/strength);
        pxl.b += (pxl.b - m_data[index(k+1, i)].b) * (1/strength);

        if(left)
        {
          pxl.r += (pxl.r - m_data[index(k+1, i-1)].r) * (1/strength);
          pxl.g += (pxl.g - m_data[index(k+1, i-1)].g) * (1/strength);
          pxl.b += (pxl.b - m_data[index(k+1, i-1)].b) * (1/strength);
        }
      }
      //cout << "finished this pixel" << endl;
      data[index(k, i)] = pxl;
    }
  }
  m_data = data;
}

void Image::sharpen() {
  //cout << "Sharpening <3" << endl;
  int strength = 7;
  // copy&pasta

  //Pixel[m_height*m_width] data;
  Pixel* data = new Pixel[m_height*m_width];

  for (unsigned int i = 0; i< m_width*m_height; ++i){
    data[i] = m_data[i];
  }

  for (unsigned int i=0; i< m_width; i++) {
    for (unsigned int k=0; k< m_height; k++) {
      Pixel pxl;
      pxl = m_data[index(k, i)];
      bool right = false;
      bool left = false;
      //Saman rivin viereiset pikselit
      if (i+1 < m_width) {
        data[index(k, i+1)].r -= pxl.r * (1/strength);
        data[index(k, i+1)].g -= pxl.g * (1/strength);
        data[index(k, i+1)].b -= pxl.b * (1/strength);
        right = true;
      }
      if ((int)i-1 >= 0)
      {
        data[index(k, i-1)].r -= pxl.r * (1/strength);
        data[index(k, i-1)].g -= pxl.g * (1/strength);
        data[index(k, i-1)].b -= pxl.b * (1/strength);
        left = true;
      }
      //Yläpikselit
      if ((int)k-1 >= 0)
      {
        if (right)
        {
          data[index(k-1, i+1)].r -= pxl.r * (1/strength);
          data[index(k-1, i+1)].g -= pxl.g * (1/strength);
          data[index(k-1, i+1)].b -= pxl.b * (1/strength);
        }

        data[index(k-1, i)].r -= pxl.r * (1/strength);
        data[index(k-1, i)].g -= pxl.g * (1/strength);
        data[index(k-1, i)].b -= pxl.b * (1/strength);
        if (left)
        {
          data[index(k-1, i-1)].r -= pxl.r * (1/strength);
          data[index(k-1, i-1)].g -= pxl.g * (1/strength);
          data[index(k-1, i-1)].b -= pxl.b * (1/strength);
        }
      }

      //Alapikselit
      if (k+1 < m_height)
      {
        if (right)
        {
          data[index(k+1, i+1)].r -= pxl.r * (1/strength);
          data[index(k+1, i+1)].g -= pxl.g * (1/strength);
          data[index(k+1, i+1)].b -= pxl.b * (1/strength);
        }

        data[index(k+1, i)].r -= pxl.r * (1/strength);
        data[index(k+1, i)].g -= pxl.g * (1/strength);
        data[index(k+1, i)].b -= pxl.b * (1/strength);

        if(left)
        {
          data[index(k+1, i-1)].r -= pxl.r * (1/strength);
          data[index(k+1, i-1)].g -= pxl.g * (1/strength);
          data[index(k+1, i-1)].b -= pxl.b * (1/strength);
        }
      }
    }
  }
  m_data = data;
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
