//
// Created by hewis on 12/04/2021.
//

#include "Utilities/ControllerTracker.h"

#include <utility>
ControllerTracker::ControllerTracker(ASGE::Input* _input) : input(_input)
{
  for (auto& controller : button_bindings)
  {
    for (size_t i = 0; i < 14; i++)
    {
      controller.insert(std::make_pair(i, i));
    }
  }
  for (auto& controller : axis_bindings)
  {
    for (size_t i = 0; i < 6; i++)
    {
      controller.insert(std::make_pair(i, i));
    }
  }
}
void ControllerTracker::updateInput()
{
  size_t index = 0;
  for (auto& gamepad : old_data)
  {
    gamepad = CONTROLLER::LocalController();
    if (!input->getGamePad(static_cast<int>(index)).is_connected)
    {
      continue;
    }
    gamepad.buttons = new_data[index].buttons;
    gamepad.axis    = new_data[index].axis;
    index++;
  }
  index = 0;
  for (auto& gamepad : new_data)
  {
    gamepad = CONTROLLER::LocalController();
    if (!input->getGamePad(static_cast<int>(index)).is_connected)
    {
      continue;
    }
    const auto& new_stuff = input->getGamePad(static_cast<int>(index));
    for (size_t i = 0; i < static_cast<size_t>(new_stuff.no_of_buttons); i++)
    {
      gamepad.buttons[i] = static_cast<bool>(new_stuff.buttons[i]);
    }
    for (size_t i = 0; i < static_cast<size_t>(new_stuff.no_of_axis); i++)
    {
      gamepad.axis[i] = new_stuff.axis[i];
    }
    index++;
  }
}
bool ControllerTracker::getButton(size_t controller_index, size_t button)
{
  if (static_cast<int>(button) >= input->getGamePad(static_cast<int>(controller_index)).no_of_buttons)
  {
    return false;
  }
  return new_data[controller_index].buttons[button_bindings[controller_index][button]];
}
bool ControllerTracker::getButtonUp(size_t controller_index, size_t button)
{
  if (static_cast<int>(button) >= input->getGamePad(static_cast<int>(controller_index)).no_of_buttons)
  {
    return false;
  }
  auto up = !new_data[controller_index].buttons[button_bindings[controller_index][button]];
  return up && old_data[controller_index].buttons[button_bindings[controller_index][button]];
}
bool ControllerTracker::getButtonDown(size_t controller_index, size_t button)
{
  if (static_cast<int>(button) >= input->getGamePad(static_cast<int>(controller_index)).no_of_buttons)
  {
    return false;
  }
  auto down = new_data[controller_index].buttons[button_bindings[controller_index][button]];
  return down && !old_data[controller_index].buttons[button_bindings[controller_index][button]];
}
float ControllerTracker::getAxis(size_t controller_index, size_t axis)
{
  if (static_cast<int>(axis) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return 0;
  }
  auto value = new_data[controller_index].axis[axis_bindings[controller_index][axis]];
  if (std::fabs(value) < CONTROLLER::AXIS_DEADZONE)
  {
    return 0;
  }
  return value;
}
bool ControllerTracker::getAxisUp(size_t controller_index, size_t axis)
{
  if (static_cast<int>(axis) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return false;
  }
  auto up = new_data[controller_index].axis[axis_bindings[controller_index][axis]] >=
            CONTROLLER::AXIS_DEADZONE;
  return up && old_data[controller_index].axis[axis_bindings[controller_index][axis]] <
                 CONTROLLER::AXIS_DEADZONE;
}
bool ControllerTracker::getAxisDown(size_t controller_index, size_t axis)
{
  if (static_cast<int>(axis) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return false;
  }
  auto up = new_data[controller_index].axis[axis_bindings[controller_index][axis]] <=
            -CONTROLLER::AXIS_DEADZONE;
  return up && old_data[controller_index].axis[axis_bindings[controller_index][axis]] >
                 -CONTROLLER::AXIS_DEADZONE;
}
ASGE::Point2D ControllerTracker::getStick(size_t controller_index, size_t stick)
{
  if (static_cast<int>(stick * 2 + 1) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return ASGE::Point2D();
  }
  auto value = ASGE::Point2D(
    new_data[controller_index].axis[axis_bindings[controller_index][stick * 2]],
    new_data[controller_index].axis[axis_bindings[controller_index][stick * 2 + 1]]);
  if (std::hypotf(value.x, value.y) < CONTROLLER::AXIS_DEADZONE)
  {
    return ASGE::Point2D();
  }
  return value;
}
void ControllerTracker::setBinding(
  size_t controller_index, std::unordered_map<size_t, size_t> _button_bindings,
  std::unordered_map<size_t, size_t> _axis_bindings)
{
  button_bindings[controller_index] = std::move(_button_bindings);
  axis_bindings[controller_index]   = std::move(_axis_bindings);
}
int ControllerTracker::getLastButton(size_t controller_index)
{
  const auto& controller = input->getGamePad(static_cast<int>(controller_index));
  for (int i = 0; i < controller.no_of_buttons; i++)
  {
    if (
      static_cast<bool>(controller.buttons[i]) &&
      !old_data[controller_index].buttons[static_cast<size_t>(i)])
    {
      return i;
    }
  }
  return -1;
}
int ControllerTracker::getLastAxis(size_t controller_index)
{
  const auto& controller = input->getGamePad(static_cast<int>(controller_index));
  for (int i = 0; i < controller.no_of_axis; i++)
  {
    if (
      std::fabs(controller.axis[i]) >= CONTROLLER::AXIS_DEADZONE &&
      std::fabs(old_data[controller_index].axis[static_cast<size_t>(i)]) <
        CONTROLLER::AXIS_DEADZONE)
    {
      return i;
    }
  }
  return -1;
}
