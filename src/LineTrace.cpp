//
// Created by Bread on 19/04/2021.
//

#include "ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <cmath>

LineTrace::LineTrace(ASGE::Renderer* renderer) : line(renderer, "data/images/weapons/tracer.png", 0)
{
  line.zOrder(1);
  line.visibility(false);
}
void LineTrace::render(ASGE::Renderer* renderer)
{
  line.render(renderer);
}

void LineTrace::update(float dt)
{
  if (tracer_timer > 0)
  {
    line.opacity(tracer_timer / tracer_time);
    tracer_timer -= dt;
    if (tracer_timer <= 0)
    {
      tracer_timer = 0;
      line.visibility(false);
    }
  }
}
void LineTrace::setLine(
  ASGE::Point2D origin, ASGE::Point2D end, float time, float width, float falloff)
{
  auto diff = ASGE::Point2D(end.x - origin.x, end.y - origin.y);
  auto mag  = std::hypot(diff.x, diff.y);
  line.rotation(std::atan2(diff.y, diff.x));
  line.dimensions(ASGE::Point2D(mag, width));
  line.centrePos(origin.midpoint(end));
  line.visibility(true);
  line.opacity(1);
  line.srcRect(0, 0, falloff * line.getTextureSize().x, 1);
  tracer_timer = time;
  tracer_time  = time;
}
