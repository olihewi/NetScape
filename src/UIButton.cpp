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
  image_size = sprites[0]->getTexture()->getHeight() / 2;
  text.centrePos(ASGE::Point2D(
    sprites[4]->xPos() + sprites[4]->width() / 2,
    sprites[4]->yPos() + sprites[4]->height() / 2 + 20));
}
void UIButton::update(InputTracker& input, float /*dt*/)
{
  if (input.hasHadMouseInput())
  {
    select(isInside(input.getMousePos()));
  }
  if (
    input.getMouseButtonDown(MOUSE::LEFT_CLICK) ||
    input.getControllerButtonDown(0, CONTROLLER::BUTTONS::A))
  {
    press();
  }
}
void UIButton::render(ASGE::Renderer* renderer)
{
  ScalableSprite::render(renderer);
  text.render(renderer);
}
void UIButton::select(bool _selection)
{
  if (_selection != is_selected)
  {
    float offset = (_selection ? image_size : -image_size);
    for (auto& sprite : sprites)
    {
      auto* src = sprite->srcRect();
      src[1]    = src[1] + offset;
    }
    is_selected = _selection;
  }
}
bool UIButton::press()
{
  if (is_selected)
  {
    callback();
  }
  return is_selected;
}
