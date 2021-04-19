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

  [[nodiscard]] bool getKey(int _key);
  [[nodiscard]] bool getKeyDown(int _key);
  [[nodiscard]] bool getKeyUp(int _key);

  [[nodiscard]] bool getMouseButton(int _button);
  [[nodiscard]] bool getMouseButtonDown(int _button);
  [[nodiscard]] bool getMouseButtonUp(int _button);
  [[nodiscard]] ASGE::Point2D getMousePos();
  [[nodiscard]] ASGE::Point2D getMouseDelta();
  [[nodiscard]] ASGE::Point2D getMouseScroll();

  [[nodiscard]] bool getControllerButton(size_t _controller_index, size_t _button);
  [[nodiscard]] bool getControllerButtonDown(size_t _controller_index, size_t _button);
  [[nodiscard]] bool getControllerButtonUp(size_t _controller_index, size_t _button);
  [[nodiscard]] float getControllerAxis(size_t _controller_index, size_t _axis);
  [[nodiscard]] bool getControllerAxisUp(size_t _controller_index, size_t _axis);
  [[nodiscard]] bool getControllerAxisDown(size_t _controller_index, size_t _axis);
  [[nodiscard]] ASGE::Point2D getControllerStick(size_t _controller_index, size_t _stick);

  [[nodiscard]] bool hasHadMouseInput();

  void setControllerBinding(
    size_t controller_index, std::unordered_map<size_t, size_t> _button_bindings,
    std::unordered_map<size_t, size_t> _axis_bindings);
  [[nodiscard]] int getLastController();
  [[nodiscard]] int getLastControllerButton(size_t _controller_index);
  [[nodiscard]] int getLastControllerAxis(size_t _controller_index);

 private:
  KeyboardTracker keyboard;
  MouseTracker mouse;
  ControllerTracker controller;
};

#endif // ASGEMOVIEGAME_INPUTTRACKER_H
