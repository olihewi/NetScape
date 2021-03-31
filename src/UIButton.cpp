//
// Created by hewis on 31/03/2021.
//

#include "GameObjects/UI/UIButton.h"
#include <utility>

UIButton::UIButton(
  ASGE::Renderer* renderer, const std::string& file_path, const std::string& _text, int font_index,
  std::function<void()> _callback, std::array<float, 6> part_sizes, ASGE::Point2D _position,
  ASGE::Point2D _dimensions) :
  ScalableSprite(renderer, file_path, part_sizes, _position, _dimensions),
  text(
    renderer, _text,
    ASGE::Point2D(_position.x + part_sizes[0] + 4, _position.y + part_sizes[1] + part_sizes[3]),
    font_index),
  callback(std::move(_callback))
{
}
void UIButton::clickInput(const ASGE::ClickEvent* click)
{
  if (isInside(ASGE::Point2D(static_cast<float>(click->xpos), static_cast<float>(click->ypos))))
  {
    callback();
  }
}
