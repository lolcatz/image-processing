#ifndef H_PPM
#define H_PPM

#include <string>

struct Image {
  unsigned m_width;
  unsigned m_height;
  unsigned m_maxval;
  unsigned char* m_data;

  static Image readPPM(const std::string&);
  Image(unsigned, unsigned, unsigned);

  void sharpen();
  void smoothen();
};

#endif

