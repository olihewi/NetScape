//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_LINETRACE_H
#define ASGEMOVIEGAME_LINETRACE_H

#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
#include <Engine/Point2D.hpp>

class LineTrace
{
 public:
  explicit LineTrace(ASGE::Renderer* renderer);

  void setLine(ASGE::Point2D origin, ASGE::Point2D end, float time = 0.1F, float width = 3);

  void render(ASGE::Renderer* renderer);

  void update(float dt);

  Sprite line;
  float hit_dist = 0;

 private:
  float tracer_timer = 0;
};

#endif // ASGEMOVIEGAME_LINETRACE_H
