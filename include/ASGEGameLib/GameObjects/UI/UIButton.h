//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_UIBUTTON_H
#define ASGEMOVIEGAME_UIBUTTON_H

#include "ScalableSprite.h"
#include <GameObjects/Sprites/Text.h>
#include <functional>
class UIButton : public ScalableSprite
{
 public:
  UIButton(
    ASGE::Renderer* renderer, const std::string& file_path, const std::string& _text,
    int font_index, std::function<void()> _callback, std::array<float, 6> part_sizes,
    ASGE::Point2D _position, ASGE::Point2D _dimensions);
  void clickInput(const ASGE::ClickEvent* click) override;

 private:
  Text text;
  std::function<void()> callback;
};

#endif // ASGEMOVIEGAME_UIBUTTON_H
