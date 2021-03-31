//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_GAMEOBJECT_H
#define ASGEMOVIEGAME_GAMEOBJECT_H

#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>

class GameObject
{
 public:
  virtual ~GameObject() = default;

  virtual void keyInput(const ASGE::KeyEvent* /*key*/) {}
  virtual void clickInput(const ASGE::ClickEvent* /*click*/) {}
  virtual void mouseInput(const ASGE::MoveEvent* /*mouse*/) {}
  virtual void scrollInput(const ASGE::ScrollEvent* /*scroll*/) {}

  virtual void update(float /*dt*/) {}
  virtual void render(ASGE::Renderer* /*renderer*/) {}
};

#endif // ASGEMOVIEGAME_GAMEOBJECT_H
