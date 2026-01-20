// * atlas *
// Juliet Colman 2026

#include <iostream>
#include <blit.h>
#include <sprite_sheet.h>
#include "commandline.h"
#include "grid_decorator.h"
#include "replace.h"
#include "save.h"

bool create_check_params(
  commandline& cl, int& sx, int& sy, int& cx, int& cy, bool& overwrite_file);

bool create(commandline& cl)
{
  int sx = 0;
  int sy = 0;
  int cx = 1;
  int cy = 1;
  bool overwrite_file = false;

  if (!create_check_params(cl, sx, sy, cx, cy, overwrite_file))
  {
    return false;
  }

  auto dest_image = std::make_shared<image_32>(sx, sy);
  if (cx > 1 || cy > 1)
  {
    auto grid = std::make_shared<grid_decorator>(dest_image, cx, cy);
    p_image dest = std::static_pointer_cast<image>(dest_image);
    blit<overwrite>(grid, dest, 0, 0);
  }

  auto filename = *cl.get(2);
 
  return save::save_file(dest_image, filename, overwrite_file);
}

bool create_check_params(
  commandline& cl, int& sx, int& sy, int& cx, int& cy, bool& overwrite_file)
{
  overwrite_file = check_flag(cl, "--overwrite");

  // With flags removed, there should be 5 (no cells) or 7 (with cells) params.
  const int n = cl.num_strings();
  if (n != 5 && n != 7)
  {
    std::cout << "Bad number of params for create.\n";
    return false;
  }
  
  auto opt_sx = cl.get<int>(3);
  if (!opt_sx || *opt_sx < 1)
  {
    std::cout << "Bad size in x.\n";
    return false;
  }
  sx = *opt_sx;

  auto opt_sy = cl.get<int>(4);
  if (!opt_sy || *opt_sy < 1)
  {
    std::cout << "Bad size in y.\n";
    return false;
  }
  sy = *opt_sy;

  // Num cells params can be missing
  auto opt_cx = cl.get<int>(5);
  if (opt_cx) 
  {
    if (*opt_cx < 1) 
    {
      std::cout << "Bad number of cells in x.\n";
      return false;
    }
    cx = *opt_cx;
  
    auto opt_cy = cl.get<int>(6);
    if (!opt_cy || *opt_cy < 1)
    {
      std::cout << "Bad number of cells in y.\n";
      return false;
    }
    cy = *opt_cy;
  }

  return true;
}

