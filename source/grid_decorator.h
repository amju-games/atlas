// * atlas *
// Juliet Colman 2026

#include <image_decorator.h> // lo-res

struct grid_decorator : public image_decorator
{
  grid_decorator(p_image child, int cx, int cy) : m_cx(cx), m_cy(cy)
  {
    set_child(child);
  }

  colour get_colour(int x, int y) const override 
  {
    const int sx = get_width();
    const int sy = get_height();
    int i = (x * m_cx / sx) % 2;
    int j = (y * m_cy / sy) % 2;
    int k = i ^ j;
    k *= 0xff;
    return colour(k, k, k, 0xff);
  }

  int m_cx = 1;
  int m_cy = 1;
};

