//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_EDITORTILESET_H
#define ASGEMOVIEGAME_EDITORTILESET_H

#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
#include <ASGEGameLib/GameObjects/UI/ScalableSprite.h>
class EditorTileSet : public GameObject
{
 public:
  EditorTileSet(ASGE::Renderer* renderer, const std::string& file_path, int _sprite_size = 32);
  void render(ASGE::Renderer* renderer) override;
  void clickInput(const ASGE::ClickEvent* click) override;
  [[nodiscard]] std::array<float, 4> getCurrentRect();

 private:
  Sprite sprite_sheet;
  ScalableSprite cursor;
  int sprite_size;
  int selection_start = 0;
  int selection_end   = 0;
};

#endif // ASGEMOVIEGAME_EDITORTILESET_H
