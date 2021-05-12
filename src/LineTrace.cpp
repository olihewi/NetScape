//
// Created by Bread on 19/04/2021.
//

#include "ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <cmath>

LineTrace::LineTrace(ASGE::Renderer* renderer) :
  line(renderer, "data/images/ui/player_health_bar.png", 0)
{
  line.zOrder(1);
}
void LineTrace::render(ASGE::Renderer* renderer)
{
  line.render(renderer);
}

void LineTrace::update(float dt)
{
  if (tracer_timer > 0)
  {
    tracer_timer -= dt;
    if (tracer_timer <= 0)
    {
      tracer_timer = 0;
      line.visibility(false);
    }
  }
}
void LineTrace::setLine(ASGE::Point2D origin, ASGE::Point2D end, float time, float width)
{
  auto diff = ASGE::Point2D(end.x - origin.x, end.y - origin.y);
  auto mag  = std::hypot(diff.x, diff.y);
  line.rotation(std::atan2(diff.y, diff.x));
  line.dimensions(ASGE::Point2D(mag, width));
  line.centrePos(origin.midpoint(end));
  line.visibility(true);
  tracer_timer = time;
}
