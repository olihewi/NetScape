//
// Created by hewis on 01/04/2021.
//

#include "Utilities/FontManager.h"
#include <Engine/FileIO.h>
int FontManager::loadFont(ASGE::Renderer* renderer, const std::string& file_path, int font_size)
{
  ASGE::FILEIO::File font_file = ASGE::FILEIO::File();
  if (font_file.open(file_path))
  {
    ASGE::FILEIO::IOBuffer file_buffer = font_file.read();
    if (file_buffer.length != 0U)
    {
      return renderer->loadFontFromMem(
        file_path.c_str(),
        file_buffer.as_unsigned_char(),
        static_cast<unsigned int>(file_buffer.length),
        font_size);
    }
  }
  return -1;
}
void FontManager::loadFonts(ASGE::Renderer* renderer)
{
  /// Load required fonts here!
  loadFont(renderer, "data/fonts/RobotoMono-Regular.ttf", 48);
}
