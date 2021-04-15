//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_UIBUTTON_H
#define ASGEMOVIEGAME_UIBUTTON_H

#include "ScalableSprite.h"
#include <ASGEGameLib/GameObjects/Sprites/Text.h>
#include <functional>
class UIButton : public ScalableSprite
{
 public:
  UIButton(
    ASGE::Renderer* renderer, const std::string& file_path, const std::string& _text,
    int font_index, std::function<void()> _callback, std::array<float, 6> part_sizes,
    ASGE::Point2D _position, ASGE::Point2D _dimensions);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

  void select(bool _selection);
  bool press();

 private:
  Text text;
  std::function<void()> callback;
  bool is_selected = false;
  float image_size = 0;
};

#endif // ASGEMOVIEGAME_UIBUTTON_H
