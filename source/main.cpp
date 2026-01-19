// * atlas *
// Juliet Colman 2026

#include <iostream>
#include <image_32.h> // from lo-res library
#include <sprite_sheet.h> // from lo-res library
#include "commandline.h"
#include "replace.h"

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

int main(int argc, const char** argv)
{
  commandline c(argc, argv);
  int ret = 0;
  auto action = c.get(1);
  if (action && *action == "replace")
  {
    if (replace::replace(c))
    {
      return 0;
    }
    return 1;
  }
  print_help();
  return ret;
}

