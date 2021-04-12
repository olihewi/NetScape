//
// Created by hewis on 12/04/2021.
//

#include "Utilities/ControllerTracker.h"
ControllerTracker::ControllerTracker(ASGE::Input* _input) : input(_input) {}
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
    for (unsigned char& button : new_data[index].buttons)
    {
      gamepad.buttons.emplace_back(button);
    }
    for (float& axi : new_data[index].axis)
    {
      gamepad.axis.emplace_back(axi);
    }
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
    for (int i = 0; i < new_stuff.no_of_buttons; i++)
    {
      gamepad.buttons.emplace_back(new_stuff.buttons[static_cast<size_t>(i)]);
    }
    for (int i = 0; i < new_stuff.no_of_axis; i++)
    {
      gamepad.axis.emplace_back(new_stuff.axis[static_cast<size_t>(i)]);
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
  return static_cast<bool>(new_data[controller_index].buttons[button]);
}
bool ControllerTracker::getButtonUp(size_t controller_index, size_t button)
{
  if (static_cast<int>(button) >= input->getGamePad(static_cast<int>(controller_index)).no_of_buttons)
  {
    return false;
  }
  auto up = !static_cast<bool>(new_data[controller_index].buttons[button]);
  return up && static_cast<bool>(old_data[controller_index].buttons[button]);
}
bool ControllerTracker::getButtonDown(size_t controller_index, size_t button)
{
  if (static_cast<int>(button) >= input->getGamePad(static_cast<int>(controller_index)).no_of_buttons)
  {
    return false;
  }
  auto down = static_cast<bool>(new_data[controller_index].buttons[button]);
  return down && !static_cast<bool>(old_data[controller_index].buttons[button]);
}
float ControllerTracker::getAxis(size_t controller_index, size_t axis)
{
  if (static_cast<int>(axis) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return 0;
  }
  return new_data[controller_index].axis[axis];
}
bool ControllerTracker::getAxisUp(size_t controller_index, size_t axis)
{
  if (static_cast<int>(axis) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return false;
  }
  auto up = new_data[controller_index].axis[axis] >= CONTROLLER::AXIS_DEADZONE;
  return up && old_data[controller_index].axis[axis] < CONTROLLER::AXIS_DEADZONE;
}
bool ControllerTracker::getAxisDown(size_t controller_index, size_t axis)
{
  if (static_cast<int>(axis) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return false;
  }
  auto up = new_data[controller_index].axis[axis] <= -CONTROLLER::AXIS_DEADZONE;
  return up && old_data[controller_index].axis[axis] > -CONTROLLER::AXIS_DEADZONE;
}
ASGE::Point2D ControllerTracker::getStick(size_t controller_index, size_t stick)
{
  if (static_cast<int>(stick * 2 + 1) >= input->getGamePad(static_cast<int>(controller_index)).no_of_axis)
  {
    return ASGE::Point2D();
  }
  return ASGE::Point2D(
    new_data[controller_index].axis[stick * 2], new_data[controller_index].axis[stick * 2 + 1]);
}
