// * atlas *
// Juliet Colman 2026

#pragma once

#include <string>
#include <image_32.h>

namespace save
{
bool save_file(
  std::shared_ptr<image_32> dest_image, 
  std::string filename,
  bool overwrite);
}

