#ifndef H_IMAGE
#define H_IMAGE

#include <string>
#include <fstream>
#include "pixel.h"

struct Image {
  unsigned m_width;
  unsigned m_height;
  unsigned m_maxval;
  Pixel* m_data;

  Image(unsigned, unsigned, unsigned);
  ~Image();

  static Image readPPM(const std::string&);

  unsigned index(unsigned, unsigned);
  Image sharpen();
  Image smoothen();
  std::ostream& printPPM(std::ostream&);
};

#endif

