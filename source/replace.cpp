// * atlas *
// Juliet Colman 2026

#include <iostream>
#include <blend.h>
#include <sprite_sheet.h>
#include "commandline.h"
#include "mask_decorator.h"
#include "replace.h"
#include "save.h"

namespace replace
{
bool replace_check_params(
  commandline& cl, int& cx, int& cy, int& cell, bool& force, bool& overwrite, bool& mask);

bool check_load_image(p_image image, const std::string& filename);

bool replace_check_image(commandline& cl, p_image image, int param);

bool do_replace(p_image src, p_image dest, int cx, int cy, int cell);

bool misgivings_check(p_image src, p_image dest, int cx, int cy, int cell);


bool replace(commandline& cl)
{
  int cx = 0;
  int cy = 0;
  int cell = 0;
  bool force = false;
  bool overwrite = false;
  bool mask = false;

  if (!replace_check_params(cl, cx, cy, cell, force, overwrite, mask))
  {
    return false;
  }

  auto src_image = std::make_shared<image_32>();
  if (!replace_check_image(cl, src_image, 2))
  {
    return false;
  }

  auto dest_image = std::make_shared<image_32>();
  if (!replace_check_image(cl, dest_image, 3))
  {
    return false;
  }

  bool has_misgivings = misgivings_check(src_image, dest_image, cx, cy, cell);
  if (has_misgivings && !force)
  {
    return false;
  }

  // If mask flag is true, wrap a decorator around the source image
  auto src = mask ? std::static_pointer_cast<image>(
    std::make_shared<mask_decorator>(src_image)) : 
    std::static_pointer_cast<image>(src_image);

  do_replace(src, dest_image, cx, cy, cell);

  return save::save_file(dest_image, *cl.get(3), overwrite);
}

bool check_flag(commandline& cl, const std::string& flag)
{
  bool ret = cl.contains(flag);
  cl.remove_string(flag);
  return ret;
}

bool replace_check_params(
  commandline& cl, int& cx, int& cy, int& cell, bool& force, bool& overwrite, bool& mask)
{
  force = check_flag(cl, "--force");
  overwrite = check_flag(cl, "--overwrite");
  mask = check_flag(cl, "--mask");

  // With flags removed, there should be 7 params.
  if (cl.num_strings() != 7)
  {
    std::cout << "Bad number of params for replace.\n";
    return false;
  }
  auto opt_cx = cl.get<int>(4);
  if (!opt_cx || *opt_cx < 1)
  {
    std::cout << "Bad number of cells in x.\n";
    return false;
  }
  cx = *opt_cx;
  auto opt_cy = cl.get<int>(5);
  if (!opt_cy || *opt_cy < 1)
  {
    std::cout << "Bad number of cells in y.\n";
    return false;
  }
  cy = *opt_cy;
  auto opt_cell = cl.get<int>(6);
  if (!opt_cell || *opt_cell < 0 || *opt_cell >= (cx * cy))
  {
    std::cout << "Bad cell number, should be [0.." << cx*cy << ").\n";
    return false;
  }
  cell = *opt_cell;

  return true;
}

bool check_load_image(p_image image, const std::string& filename)
{ 
  if (!image->load(filename))
  { 
    std::cout << "Failed to load image \"" << filename << "\".\n";
    return false;
  }
  return true;
}

bool replace_check_image(commandline& cl, p_image image, int param)
{
  auto opt_filename = cl.get(param);
  if (!opt_filename)
  {
    std::cout << "Bad image filename.\n";
    return false;
  }
  auto filename = *opt_filename;
  if (!check_load_image(image, filename))
  {
    std::cout << "Failed to load image \"" << filename << "\".\n";
    return false;
  }
  return true;
}

bool do_replace(p_image src, p_image dest, int cx, int cy, int cell)
{
  sprite_sheet ss;
  ss.set_image(dest);
  ss.set_num_cells(cx, cy);
  // TODO other blending options?
  ss.draw_into_cell<overwrite>(src, cell);
  return true;
}

bool misgivings_check(p_image src, p_image dest, int cx, int cy, int cell)
{
  bool ret = false; // no misgivings
  if (   src->get_width() > dest->get_width()
      || src->get_height() > dest->get_height())
  {
    std::cout << "MISGIVING: src size is bigger than dest? Images wrong way round?\n";
    ret = true;
  }
  return ret;
}

}

