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
  image_size += sprites[0]->srcRect()[3];
  image_size += sprites[3]->srcRect()[3];
  image_size += sprites[6]->srcRect()[3];
  text.centrePos(ASGE::Point2D(
    sprites[4]->xPos() + sprites[4]->width() / 2,
    sprites[4]->yPos() + sprites[4]->height() / 2 + 20));
}
void UIButton::clickInput(const ASGE::ClickEvent* click)
{
  if (isInside(ASGE::Point2D(static_cast<float>(click->xpos), static_cast<float>(click->ypos))))
  {
    callback();
  }
}
void UIButton::mouseInput(const ASGE::MoveEvent* mouse)
{
  bool last_selected = is_selected;
  is_selected =
    isInside(ASGE::Point2D(static_cast<float>(mouse->xpos), static_cast<float>(mouse->ypos)));
  if (last_selected != is_selected)
  {
    for (auto& sprite : sprites)
    {
      auto* src    = sprite->srcRect();
      float offset = (is_selected ? image_size : -image_size);
      src[1]       = src[1] + offset;
    }
  }
}
void UIButton::render(ASGE::Renderer* renderer)
{
  ScalableSprite::render(renderer);
  text.render(renderer);
}
