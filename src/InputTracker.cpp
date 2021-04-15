//
// Created by hewis on 15/04/2021.
//

#include "Utilities/InputTracker.h"
#include <cmath>
InputTracker::InputTracker(ASGE::Input* _input) :
  keyboard(_input), mouse(_input), controller(_input)
{
}
void InputTracker::update()
{
  keyboard.updateInput();
  mouse.updateInput();
  controller.updateInput();
}
bool InputTracker::getKey(int _key)
{
  return keyboard.getKey(_key);
}
bool InputTracker::getKeyDown(int _key)
{
  return keyboard.getKeyDown(_key);
}
bool InputTracker::getKeyUp(int _key)
{
  return keyboard.getKeyUp(_key);
}
bool InputTracker::getMouseButton(int _button)
{
  return mouse.getButton(_button);
}
bool InputTracker::getMouseButtonDown(int _button)
{
  return mouse.getButtonDown(_button);
}
bool InputTracker::getMouseButtonUp(int _button)
{
  return mouse.getButtonUp(_button);
}
ASGE::Point2D InputTracker::getMousePos()
{
  return mouse.getMousePos();
}
ASGE::Point2D InputTracker::getMouseDelta()
{
  return mouse.getMouseDelta();
}
ASGE::Point2D InputTracker::getMouseScroll()
{
  return mouse.getScroll();
}
bool InputTracker::getControllerButton(size_t _controller_index, size_t _button)
{
  return controller.getButton(_controller_index, _button);
}
bool InputTracker::getControllerButtonDown(size_t _controller_index, size_t _button)
{
  return controller.getButtonDown(_controller_index, _button);
}
bool InputTracker::getControllerButtonUp(size_t _controller_index, size_t _button)
{
  return controller.getButtonUp(_controller_index, _button);
}
float InputTracker::getControllerAxis(size_t _controller_index, size_t _axis)
{
  return controller.getAxis(_controller_index, _axis);
}
bool InputTracker::getControllerAxisUp(size_t _controller_index, size_t _axis)
{
  return controller.getAxisUp(_controller_index, _axis);
}
bool InputTracker::getControllerAxisDown(size_t _controller_index, size_t _axis)
{
  return controller.getAxisDown(_controller_index, _axis);
}
ASGE::Point2D InputTracker::getControllerStick(size_t _controller_index, size_t _stick)
{
  return controller.getStick(_controller_index, _stick);
}
bool InputTracker::hasHadMouseInput()
{
  auto mouse_delta = mouse.getMouseDelta();
  return (std::fabs(mouse_delta.x) >= 0.1F || std::fabs(mouse_delta.y) >= 0.1F);
}
