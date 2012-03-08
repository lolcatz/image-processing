#include "image.h"

Image::Image(unsigned width, unsigned height, unsigned maxval):
  m_width(width),
  m_height(height),
  m_maxval(maxval),
  m_data(new unsigned char[width*height])
{
}

Image Image::readPPM(const std::string& /*filename*/) {
  Image i = Image(5, 6, 10);
  return i;

}

