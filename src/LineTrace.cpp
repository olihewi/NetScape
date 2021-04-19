//
// Created by Bread on 19/04/2021.
//

#include "../include/ASGEGameLib/Utilities/LineTrace.h"
#include <Engine/Logger.hpp>
#include <string>

LineTrace::LineTrace(size_t distance, ASGE::Point2D origin, size_t angle)
{
  hitCheck(distance, origin, angle);
}
ASGE::Point2D LineTrace::hitCheck(size_t distance, ASGE::Point2D origin, size_t angle)
{
  ASGE::Point2D end_point = {0,0};
  end_point.x = origin.x + (tan(angle * 57.2958)*origin.y);
  end_point.y = origin.y + (tan(angle * 57.2958)*origin.x);

  end_point *= distance;
  Logging::DEBUG(std::to_string(end_point.x) + " , " + std::to_string(end_point.y));

  return end_point;
}

