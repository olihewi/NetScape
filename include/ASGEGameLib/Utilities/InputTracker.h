//
// Created by hewis on 15/04/2021.
//

#ifndef ASGEMOVIEGAME_INPUTTRACKER_H
#define ASGEMOVIEGAME_INPUTTRACKER_H
#include "ControllerTracker.h"
#include "KeyboardTracker.h"
#include "MouseTracker.h"
class InputTracker
{
 public:
  explicit InputTracker(ASGE::Input* _input);

  void update();

  bool getKey(int _key);
  bool getKeyDown(int _key);
  bool getKeyUp(int _key);

  bool getMouseButton(int _button);
  bool getMouseButtonDown(int _button);
  bool getMouseButtonUp(int _button);
  ASGE::Point2D getMousePos();
  ASGE::Point2D getMouseDelta();
  ASGE::Point2D getMouseScroll();

  bool getControllerButton(size_t _controller_index, size_t _button);
  bool getControllerButtonDown(size_t _controller_index, size_t _button);
  bool getControllerButtonUp(size_t _controller_index, size_t _button);
  float getControllerAxis(size_t _controller_index, size_t _axis);
  bool getControllerAxisUp(size_t _controller_index, size_t _axis);
  bool getControllerAxisDown(size_t _controller_index, size_t _axis);
  ASGE::Point2D getControllerStick(size_t _controller_index, size_t _stick);

  bool hasHadMouseInput();

 private:
  KeyboardTracker keyboard;
  MouseTracker mouse;
  ControllerTracker controller;
};

#endif // ASGEMOVIEGAME_INPUTTRACKER_H
