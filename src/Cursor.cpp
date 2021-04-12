//
// Created by hewis on 12/04/2021.
//

#include "GameObjects/UI/Cursor.h"
Cursor::Cursor(ASGE::Renderer* renderer) : Sprite(renderer, "data/images/ui/cursors.png")
{
  float sprite_size = Sprite::dimensions().y;
  Sprite::dimensions(ASGE::Point2D(sprite_size, sprite_size));
  Sprite::srcRect(0, 0, sprite_size, sprite_size);
  Sprite::zOrder(2);
}
void Cursor::position(ASGE::Point2D _position)
{
  Sprite::position(ASGE::Point2D(
    _position.x - Sprite::dimensions().x / 2, _position.y - Sprite::dimensions().y / 2));
}
void Cursor::setCursor(Cursor::CursorMode _mode)
{
  float sprite_size = Sprite::dimensions().y;
  auto x_offset     = static_cast<float>(_mode) * sprite_size;
  Sprite::srcRect(x_offset, 0, sprite_size, sprite_size);
}
void Cursor::mouseInput(const ASGE::MoveEvent* mouse)
{
  position(ASGE::Point2D(static_cast<float>(mouse->xpos), static_cast<float>(mouse->ypos)));
}
