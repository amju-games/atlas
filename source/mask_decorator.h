// * atlas *
// Juliet Colman 2026

#include <image_decorator.h> // lo-res

struct mask_decorator : public image_decorator
{
  mask_decorator(p_image child) 
  {
    set_child(child);
  }

  colour get_colour(int x, int y) const override 
  {
    colour c = m_child->get_colour(x, y); 
    // Alpha channel becomes greyscale RBG colour
    c.a = std::clamp((c.r + c.g + c.b) / 3, 0, 0xff);
    // RGB colour set to white
    c.r = c.g = c.b = 0xff;
    return c;
  }
};

