//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_LINETRACE_H
#define ASGEMOVIEGAME_LINETRACE_H

#include <Engine/Point2D.h>


class LineTrace
{
 public:
  LineTrace(size_t distance, ASGE::Point2D origin, size_t angle);

  ASGE::Point2D hitCheck(size_t distance, ASGE::Point2D origin, size_t angle);

};

#endif // ASGEMOVIEGAME_LINETRACE_H
