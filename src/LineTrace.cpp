//
// Created by Bread on 19/04/2021.
//

#include "../include/ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <string>

LineTrace::LineTrace(float distance, ASGE::Point2D origin, float angle)
{
  hitCheck(distance, origin, angle);
}
ASGE::Point2D LineTrace::hitCheck(float distance, ASGE::Point2D origin, float angle)
{
  ASGE::Point2D end_point = { 0, 0 };
  end_point.x             = origin.x + (std::tanf(angle * 57.2958F) * origin.y);
  end_point.y             = origin.y + (std::tanf(angle * 57.2958F) * origin.x);

  end_point *= distance;
  Logging::DEBUG(std::to_string(end_point.x) + " , " + std::to_string(end_point.y));

  return end_point;
}
