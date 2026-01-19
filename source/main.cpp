// * atlas *
// Juliet Colman 2026

#include <iostream>
#include <image_32.h> // from lo-res library
#include <sprite_sheet.h> // from lo-res library
#include "commandline.h"

void print_help()
{
  std::cout << R"(atlas -- texture atlas tool -- juliet colman 2026
atlas replace <src> <dest> <cx> <cy> <c> [--force] [--overwrite]
  Replaces one cell in destination atlas image.
  src: source image png filename
  dest: destination image png filename
  cx: number of cells in x
  cy: number of cells in y
  c: cell to replace [0 .. cx * cy)
  --force: continue despite misgivings
  --overwrite: overwrite destination image
)";
}

bool replace_check_params(
  commandline& cl, int& cx, int& cy, int& cell, bool& force, bool& overwrite)
{
  force = cl.contains("--force");
  cl.remove_string("--force");

  overwrite = cl.contains("--overwrite");
  cl.remove_string("--overwrite");

  if (cl.num_strings() < 7)
  {
    std::cout << "Missing params for replace.\n";
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

bool save_file(std::shared_ptr<image_32> dest_image, std::string filename, 
  bool overwrite)
{
  if (!overwrite)
  {
    // Remove ".png" from filename
    filename.erase(
      std::find(filename.begin(), filename.end(), '.'), 
      filename.end());

    filename += "-edited.png";
  }

  if (!dest_image->save(filename))
  {
    std::cout << "Failed to save file \"" << filename << "\".\n";
    return false;
  }
  return true;
}

bool replace(commandline& cl)
{
  int cx = 0;
  int cy = 0;
  int cell = 0;
  bool force = false;
  bool overwrite = false;

  if (!replace_check_params(cl, cx, cy, cell, force, overwrite))
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
  do_replace(src_image, dest_image, cx, cy, cell);

  return save_file(dest_image, *cl.get(3), overwrite);
}

int main(int argc, const char** argv)
{
  commandline c(argc, argv);
  int ret = 0;
  auto action = c.get(1);
  if (action && *action == "replace")
  {
    if (replace(c))
    {
      return 0;
    }
    return 1;
  }
  print_help();
  return ret;
}

