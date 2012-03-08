#ifndef H_IMAGE
#define H_IMAGE

#include <string>
#include "pixel.h"

struct Image {
  unsigned m_width;
  unsigned m_height;
  unsigned m_maxval;
  Pixel* m_data;

  static Image readPPM(const std::string&);
  Image(unsigned, unsigned, unsigned);

  unsigned index(unsigned, unsigned);
  void sharpen();
  void smoothen();
  void print();
};

#endif

