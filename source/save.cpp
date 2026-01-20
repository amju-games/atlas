// * atlas *
// Juliet Colman 2026

#include <iostream>
#include <filesystem>
#include "save.h"

namespace save
{
bool save_file(std::shared_ptr<image_32> dest_image, std::string filename,
  bool overwrite)
{
  if (!overwrite && std::filesystem::exists(filename))
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
}

