//
// Created by Bread on 19/04/2021.
//

#include "ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <cmath>

LineTrace::LineTrace(ASGE::Renderer* renderer) :
  bullet_sprites(
    std::array<Sprite, 5>{ Sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0),
                           Sprite(renderer, "data/images/ui/buttons/neon/green.png", 0),
                           Sprite(renderer, "data/images/ui/buttons/neon/pink.png", 0),
                           Sprite(renderer, "data/images/ui/buttons/neon/purple.png", 0),
                           Sprite(renderer, "data/images/ui/buttons/neon/yellow.png", 0) })
{
  for (auto& bullet_sprite : bullet_sprites)
  {
    bullet_sprite.zOrder(0);
  }
}
void LineTrace::hitCheck(float distance, ASGE::Point2D origin, float angle)
{
  float segment_distance = distance / 250;

  for (size_t i = 0; i < 249; i++)
  {
    trace_points[i].x = origin.x + segment_distance * static_cast<float>(i) * std::cos(angle);
    trace_points[i].y = origin.y + segment_distance * static_cast<float>(i) * std::sin(angle);
  }

  hit_dist = origin.distance(trace_points[hit_point]);

  if (hit_dist > 249)
  {
    hit_dist = 249;
  }

  if (has_hit)
  {
    auto tracers_needed = static_cast<size_t>(hit_dist / 50);
    Logging::DEBUG(std::to_string(hit_dist));
    Logging::DEBUG(std::to_string(tracers_needed));
    for (size_t i = 0; i < tracers_needed; i++)
    {
      bullet_sprites[i].position(trace_points[(hit_point / tracers_needed * i) + 25]);
      bullet_sprites[i].dimensions(ASGE::Point2D(hit_dist/ static_cast<float>(tracers_needed), 3));
      bullet_sprites[i].rotation(angle);
      bullet_sprites[i].visibility(true);
      tracer_timer = 0;
    }
    bullet_sprites[tracers_needed].position(trace_points[(hit_point)-25]);
    has_hit = false;
  }
  else
  {
    for (size_t i = 0; i < 5 ; i++)
    {
      bullet_sprites[i].position(trace_points[(i * 50) + 25]);
      bullet_sprites[i].dimensions(ASGE::Point2D(50, 3));
      bullet_sprites[i].rotation(angle);
      bullet_sprites[i].visibility(true);
      tracer_timer = 0;
    }
  }
}
void LineTrace::render(ASGE::Renderer* renderer)
{
  for (auto& bullet_sprite : bullet_sprites)
  {
    bullet_sprite.render(renderer);
  }
}

void LineTrace::update(float dt)
{
  tracer_timer += dt;
  for (auto& bullet_sprite : bullet_sprites)
  {
    if (bullet_sprite.visibility())
    {
      if (tracer_timer >= 0.1)
      {
        trace_points.fill(0);
        bullet_sprite.visibility(false);
      }
    }
  }
  if (has_hit)
  {
    trace_points.fill(0);
  }
}
