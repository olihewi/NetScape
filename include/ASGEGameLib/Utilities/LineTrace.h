//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_LINETRACE_H
#define ASGEMOVIEGAME_LINETRACE_H

#include <Engine/Point2D.h>

class LineTrace
{
 public:
  LineTrace(float distance, ASGE::Point2D origin, float angle);

  ASGE::Point2D hitCheck(float distance, ASGE::Point2D origin, float angle);
};

#endif // ASGEMOVIEGAME_LINETRACE_H
