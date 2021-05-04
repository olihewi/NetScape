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

  ASGE::Point2D hitCheck(float distance, ASGE::Point2D origin, float angle);

  void render(ASGE::Renderer* renderer);

  void update(float dt);

  float damage = 25;
  Sprite bullet_sprite;
  std::array<ASGE::Point2D, 250> trace_points;
  ASGE::Point2D hit_point;
  bool has_hit = false;

 private:
  float tracer_timer = 0;
  std::array<Sprite, 5> test_sprites;

  // int bullet_count = 0;
};

#endif // ASGEMOVIEGAME_LINETRACE_H
