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
  Image(const Image&);
  ~Image();

  static Image readPPM(const std::string&);

  unsigned index(unsigned, unsigned);
  static Image sharpen(Image&, Image&, unsigned, unsigned);
  static Image smoothen(Image&, Image&, unsigned, unsigned);
  std::ostream& printPPM(std::ostream&);

  private:
  Image operator=(const Image&);

};

#endif

