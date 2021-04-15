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
  Cursor(ASGE::Renderer* renderer, bool visible = false);
  void position(ASGE::Point2D _position) override;
  void setCursor(CursorMode _mode);
  void update(InputTracker& input, float dt) override;
};

#endif // ASGEMOVIEGAME_CURSOR_H
