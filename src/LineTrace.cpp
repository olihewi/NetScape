//
// Created by Bread on 19/04/2021.
//

#include "../include/ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <cmath>

LineTrace::LineTrace(ASGE::Renderer* renderer) :
  bullet_sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0),
  test_sprites(std::array<Sprite, 5>{ Sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0),
                                      Sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0),
                                      Sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0),
                                      Sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0),
                                      Sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0)

  })
{

}
ASGE::Point2D LineTrace::hitCheck(float distance, ASGE::Point2D origin, float angle)
{
  ASGE::Point2D end_point = { 0, 0 };
  float segment_distance = distance / 250;

  for(int i = 0; i < 250; i++)
  {
    trace_points[i].x             = origin.x + segment_distance * i * cos(angle);
    trace_points[i].y             = origin.y + segment_distance * i * sin(angle);
  }

  for(int i = 0; i < 5; i++)
  {
    test_sprites[i].position(trace_points[i * 50]);
    test_sprites[i].rotation(angle);
    test_sprites[i].dimensions(ASGE::Point2D(100, 5));
    test_sprites[i].visibility(true);
    tracer_timer = 0;
  }

  return end_point;
}
void LineTrace::render(ASGE::Renderer* renderer)
{
  for(auto& test_sprite : test_sprites)
  {
    test_sprite.render(renderer);
  }
}

void LineTrace::update(float dt)
{
  tracer_timer += dt;
  for(auto& test_sprite : test_sprites)
  {
    if (test_sprite.visibility())
    {
      if (tracer_timer >= 0.1)
      {
        trace_points.fill(0);
        test_sprite.visibility(false);
      }
    }
  }
  if(has_hit)
  {
    trace_points.fill(0);
    has_hit = false;
  }
}
