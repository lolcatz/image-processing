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
  int strength = 3;
  // Smoothening. doing smoothed values into a new m_data
  //Pixel[m_height*m_width] data;
  Pixel* data = new Pixel[m_height*m_width];
  for (unsigned int i=1; i<=m_width; i++) {
    for (unsigned int k=1; k<=m_height; k++) {
      Pixel pxl = m_data[(i*k)-1];
      bool right = false;
      bool left = false;
      //Saman rivin viereiset pikselit
      if (i+1 < m_width) {
        pxl.r += (pxl.r - m_data[(i+1)*k-1].r) * (1/strength);
        pxl.g += (pxl.g - m_data[(i+1)*k-1].g) * (1/strength);
        pxl.b += (pxl.b - m_data[(i+1)*k-1].b) * (1/strength);
        right = true;
      }
      if (i-1 > 0)
      {
        pxl.r += (pxl.r - m_data[(i-1)*k-1].r) * (1/strength);
        pxl.g += (pxl.g - m_data[(i-1)*k-1].g) * (1/strength);
        pxl.b += (pxl.b - m_data[(i-1)*k-1].b) * (1/strength);
        left = true;
      }
      //Yläpikselit
      if (k-1 > 0)
      {
        if (right)
        {
          pxl.r += (pxl.r - m_data[(i+1)*(k-1)-1].r) * (1/strength);
          pxl.g += (pxl.g - m_data[(i+1)*(k-1)-1].g) * (1/strength);
          pxl.b += (pxl.b - m_data[(i+1)*(k-1)-1].b) * (1/strength);
        }

        pxl.r += (pxl.r - m_data[(i)*(k-1)-1].r) * (1/strength);
        pxl.g += (pxl.g - m_data[(i)*(k-1)-1].g) * (1/strength);
        pxl.b += (pxl.b - m_data[(i)*(k-1)-1].b) * (1/strength);
        if (left)
        {
          pxl.r += (pxl.r - m_data[(i-1)*(k-1)-1].r) * (1/strength);
          pxl.g += (pxl.g - m_data[(i-1)*(k-1)-1].g) * (1/strength);
          pxl.b += (pxl.b - m_data[(i-1)*(k-1)-1].b) * (1/strength);
        }
      }

      //Alapikselit
      if (k+1 < m_height)
      {
        if (right)
        {
          pxl.r += (pxl.r - m_data[(i+1)*(k+1)-1].r) * (1/strength);
          pxl.g += (pxl.g - m_data[(i+1)*(k+1)-1].g) * (1/strength);
          pxl.b += (pxl.b - m_data[(i+1)*(k+1)-1].b) * (1/strength);
        }

        pxl.r += (pxl.r - m_data[(i)*(k+1)-1].r) * (1/strength);
        pxl.g += (pxl.g - m_data[(i)*(k+1)-1].g) * (1/strength);
        pxl.b += (pxl.b - m_data[(i)*(k+1)-1].b) * (1/strength);

        if(left)
        {
          pxl.r += (pxl.r - m_data[(i-1)*(k+1)-1].r) * (1/strength);
          pxl.g += (pxl.g - m_data[(i-1)*(k+1)-1].g) * (1/strength);
          pxl.b += (pxl.b - m_data[(i-1)*(k+1)-1].b) * (1/strength);
        }
      }
      data[(i*k)-1] = pxl;
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

  for (unsigned int i=1; i<=m_width; i++) {
    for (unsigned int k=1; k<=m_height; k++) {
      Pixel pxl = m_data[(i*k)-1];
      bool right = false;
      bool left = false;
      //Saman rivin viereiset pikselit
      if (i+1 < m_width) {
        data[(i+1)*k-1].r -= pxl.r * (1/strength);
        data[(i+1)*k-1].g -= pxl.g * (1/strength);
        data[(i+1)*k-1].b -= pxl.b * (1/strength);
        right = true;
      }
      if (i-1 > 0)
      {
        data[(i-1)*k-1].r -= pxl.r * (1/strength);
        data[(i-1)*k-1].g -= pxl.g * (1/strength);
        data[(i-1)*k-1].b -= pxl.b * (1/strength);
        left = true;
      }
      //Yläpikselit
      if (k-1 > 0)
      {
        if (right)
        {
          data[(i+1)*(k-1)-1].r -= pxl.r * (1/strength);
          data[(i+1)*(k-1)-1].g -= pxl.g * (1/strength);
          data[(i+1)*(k-1)-1].b -= pxl.b * (1/strength);
        }

        data[(i)*(k-1)-1].r -= pxl.r * (1/strength);
        data[(i)*(k-1)-1].g -= pxl.g * (1/strength);
        data[(i)*(k-1)-1].b -= pxl.b * (1/strength);
        if (left)
        {
          data[(i-1)*(k-1)-1].r -= pxl.r * (1/strength);
          data[(i-1)*(k-1)-1].g -= pxl.g * (1/strength);
          data[(i-1)*(k-1)-1].b -= pxl.b * (1/strength);
        }
      }

      //Alapikselit
      if (k+1 < m_height)
      {
        if (right)
        {
          data[(i+1)*(k+1)-1].r -= pxl.r * (1/strength);
          data[(i+1)*(k+1)-1].g -= pxl.g * (1/strength);
          data[(i+1)*(k+1)-1].b -= pxl.b * (1/strength);
        }

        data[(i)*(k+1)-1].r -= pxl.r * (1/strength);
        data[(i)*(k+1)-1].g -= pxl.g * (1/strength);
        data[(i)*(k+1)-1].b -= pxl.b * (1/strength);

        if(left)
        {
          data[(i-1)*(k+1)-1].r -= pxl.r * (1/strength);
          data[(i-1)*(k+1)-1].g -= pxl.g * (1/strength);
          data[(i-1)*(k+1)-1].b -= pxl.b * (1/strength);
        }
      }
    }
  }
  m_data = data;
}

void Image::print() {
  cout << "P3" << endl;
  cout << m_width << " " << m_height << endl;
  cout << m_maxval << endl;
  for (unsigned int i = 1; i <= m_height; i++ ) {
    for (unsigned int k = 1; k <= m_width; k++ ) {
      cout << m_data[(i*k)-1].r << " ";
      cout << m_data[(i*k)-1].b << " ";
      cout << m_data[(i*k)-1].g << " ";
      cout << "   ";
    }
    cout << endl;
  }
}
