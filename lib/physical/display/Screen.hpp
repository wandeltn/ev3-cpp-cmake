#if !defined(_MSC_VER)


#include <linux/fb.h>
#include <sys/mman.h>
#include <stdint.h>
#include <memory>
#include <Logger.hpp>


#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

namespace finder::physical::display
{
  class Screen
  {
  private:
    static ::finder::log::Logger _logger;
  protected:
      int fbfd;
      uint32_t *fbp;
      size_t screensize = 0;

      unsigned int width;
      unsigned int height;
  public:
      Screen();
      ~Screen();


      void drawPixel(int x, int y, uint32_t color);
      void clear();
      void fill(uint32_t color);
  };
} // namespace finder::physical::display

#endif

#endif // !defined(_MSC_VER)
