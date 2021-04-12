//
// Created by hewis on 12/04/2021.
//

#ifndef ASGEMOVIEGAME_CURSOR_H
#define ASGEMOVIEGAME_CURSOR_H

#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
class Cursor : public Sprite
{
 public:
  enum CursorMode
  {
    POINTER,
    SELECT
  };
  explicit Cursor(ASGE::Renderer* renderer);
  void position(ASGE::Point2D _position) override;
  void setCursor(CursorMode _mode);
  void mouseInput(const ASGE::MoveEvent* mouse) override;
};

#endif // ASGEMOVIEGAME_CURSOR_H
