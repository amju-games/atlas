// * atlas *
// Juliet Colman 2026

#include <iostream>
#include "commandline.h"
#include "create.h"
#include "replace.h"

void print_help()
{
  std::cout << R"(atlas -- texture atlas tool -- juliet colman 2026
atlas replace <src> <dest> <cx> <cy> <c> [--force] [--overwrite] [--mask]
  Replaces one cell in destination atlas image.
  src: source image png filename
  dest: destination image png filename
  cx: number of cells in x
  cy: number of cells in y
  c: cell to replace [0 .. cx * cy)
  --force: continue despite misgivings
  --overwrite: overwrite destination image
  --mask: convert image into a mask (RBG->alpha)
atlas create <dest> <sx> <sy> [cx] [cy] [--overwrite]
  Creates new image with optional cell grid.
  dest: destination image png filename
  sx: image size in x
  sy: image size in y
  cx: number of cells in x
  cy: number of cells in y
  --overwrite: overwrite existing destination image
)";
}

int main(int argc, const char** argv)
{
  commandline cl(argc, argv);
  int ret = 0;
  auto action = cl.get(1);
  if (action && *action == "replace")
  {
    return replace::replace(cl) ? 0 : 1;
  }
  if (action && *action == "create")
  {
    return create(cl) ? 0 : 1;
  }
  print_help();
  return ret;
}

