//
// Created by Bread on 19/04/2021.
//

#include "../include/ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <cmath>

LineTrace::LineTrace(ASGE::Renderer* renderer) :
  bullet_sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0)
{
  bullet_sprite.visibility(false);
}
ASGE::Point2D LineTrace::hitCheck(float distance, ASGE::Point2D origin, float angle)
{
  ASGE::Point2D end_point = { 0, 0 };
  end_point.x             = origin.x + 10 + distance * cos(angle);
  end_point.y             = origin.y + 10 + distance * sin(angle);

  bullet_sprite.position(end_point);
  bullet_sprite.rotation(angle);
  bullet_sprite.dimensions(ASGE::Point2D(distance * 2, 50));
  bullet_sprite.zOrder(1);
  bullet_sprite.visibility(true);
  tracer_timer = 0;

  return end_point;
}
void LineTrace::render(ASGE::Renderer* renderer)
{
  renderer->renderText("BANG", 10, 10, ASGE::COLOURS::WHITE);
  bullet_sprite.render(renderer);
}

void LineTrace::update(float dt)
{
  tracer_timer += dt;
  if (bullet_sprite.visibility())
  {
    if (tracer_timer >= 0.1)
    {
      bullet_sprite.visibility(false);
      bullet_sprite.dimensions(ASGE::Point2D(0, 0));
    }
  }
}
