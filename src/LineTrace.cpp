//
// Created by Bread on 19/04/2021.
//

#include "../include/ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <cmath>
#include <string>

LineTrace::LineTrace(ASGE::Renderer* renderer) : Sprite(renderer, "data/images/ui/buttons/neon/blue.png", 0)
{
  Sprite::visibility(false);
}
ASGE::Point2D LineTrace::hitCheck(float distance, ASGE::Point2D origin, float angle)
{
  ASGE::Point2D end_point = { 0, 0 };
  end_point.x             = (origin.x + (tanf(angle * 57.2958F) * origin.y)) + 10;
  end_point.y             = (origin.y + (tanf(angle * 57.2958F) * origin.x)) + 10;


  Logging::DEBUG(std::to_string(end_point.x) + " , " + std::to_string(end_point.y));


  Sprite::position(ASGE::Point2D(origin.x - (distance/2), origin.y));
  Sprite::rotation(angle);
  Sprite::dimensions(ASGE::Point2D(distance, 10));

  Sprite::visibility(true);
  return end_point;
}
void LineTrace::render(ASGE::Renderer* renderer)
{
  Sprite::render(renderer);
}

