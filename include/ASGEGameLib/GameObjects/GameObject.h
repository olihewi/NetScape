//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_GAMEOBJECT_H
#define ASGEMOVIEGAME_GAMEOBJECT_H

#include <ASGEGameLib/Utilities/InputTracker.h>
#include <Engine/Renderer.hpp>

class GameObject
{
 public:
  virtual ~GameObject() = default;

  virtual void update(InputTracker& /*input*/, float /*dt*/) {}
  virtual void render(ASGE::Renderer* /*renderer*/) {}
};

#endif // ASGEMOVIEGAME_GAMEOBJECT_H
