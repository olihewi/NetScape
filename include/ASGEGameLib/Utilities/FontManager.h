//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_FONTMANAGER_H
#define ASGEMOVIEGAME_FONTMANAGER_H

#include <Engine/Renderer.hpp>

class FontManager
{
 public:
  static int loadFont(ASGE::Renderer* renderer, const std::string& file_path, int font_size);
  static void loadFonts(ASGE::Renderer* renderer);
};
namespace FONTS
{
  /// Available fonts go here
  constexpr int ROBOTO  = 1;
  constexpr int BARCODE = 2;
  constexpr int PIXEL   = 3;
}

#endif // ASGEMOVIEGAME_FONTMANAGER_H
