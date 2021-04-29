//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_LINETRACE_H
#define ASGEMOVIEGAME_LINETRACE_H

#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
#include <Engine/Point2D.hpp>

class LineTrace : public Sprite
{
 public:
  LineTrace(ASGE::Renderer* renderer);

  ASGE::Point2D hitCheck(float distance, ASGE::Point2D origin, float angle);

  void render(ASGE::Renderer* renderer) override;

  float damage = 25;
};

#endif // ASGEMOVIEGAME_LINETRACE_H
