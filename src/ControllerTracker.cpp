//
// Created by hewis on 12/04/2021.
//

#include "Utilities/ControllerTracker.h"

#include <cmath>
#include <utility>
ControllerTracker::ControllerTracker(ASGE::Input* _input) : input(_input) {}
void ControllerTracker::updateInput()
{
  /// Identify controllers to add
  int controller_i = 0;
  while (input->getGamePad(controller_i).is_connected)
  {
    bool already_tracked = false;
    for (auto& controller : controllers)
    {
      if (controller.index == controller_i)
      {
        already_tracked = true;
        break;
      }
    }
    if (!already_tracked)
    {
      const auto& this_input = input->getGamePad(controller_i);
      for (int j = 0; j < this_input.no_of_buttons; j++)
      {
        if (static_cast<bool>(this_input.buttons[j]))
        {
          controllers.emplace_back(CONTROLLER::TrackedController(controller_i));
        }
      }
    }
    controller_i++;
  }
  for (auto& controller : controllers)
  {
    controller.old_data.buttons = controller.new_data.buttons;
    controller.old_data.axis    = controller.new_data.axis;
    const auto& this_input      = input->getGamePad(controller.index);
    for (size_t i = 0; i < static_cast<size_t>(this_input.no_of_buttons); i++)
    {
      controller.new_data.buttons[i] = static_cast<bool>(this_input.buttons[i]);
    }
    for (size_t i = 0; i < static_cast<size_t>(this_input.no_of_axis); i++)
    {
      controller.new_data.axis[i] = this_input.axis[i];
      if (i >= CONTROLLER::AXIS::LEFT_TRIGGER)
      {
        controller.new_data.axis[i] /= 2;
        controller.new_data.axis[i] += 0.5F;
      }
    }
  }
}
bool ControllerTracker::getButton(size_t controller_index, size_t button)
{
  if (controller_index >= controllers.size())
  {
    return false;
  }
  return controllers[controller_index]
    .new_data.buttons[controllers[controller_index].button_bindings[button]];
}
bool ControllerTracker::getButtonUp(size_t controller_index, size_t button)
{
  if (controller_index >= controllers.size())
  {
    return false;
  }
  auto up = !controllers[controller_index]
               .new_data.buttons[controllers[controller_index].button_bindings[button]];
  return up && controllers[controller_index]
                 .old_data.buttons[controllers[controller_index].button_bindings[button]];
}
bool ControllerTracker::getButtonDown(size_t controller_index, size_t button)
{
  if (controller_index >= controllers.size())
  {
    return false;
  }
  auto down = controllers[controller_index]
                .new_data.buttons[controllers[controller_index].button_bindings[button]];
  return down && !controllers[controller_index]
                    .old_data.buttons[controllers[controller_index].button_bindings[button]];
}
float ControllerTracker::getAxis(size_t controller_index, size_t axis)
{
  if (controller_index >= controllers.size())
  {
    return 0;
  }
  auto value =
    controllers[controller_index].new_data.axis[controllers[controller_index].axis_bindings[axis]];
  if (std::fabs(value) < CONTROLLER::AXIS_DEADZONE)
  {
    return 0;
  }
  return value;
}
bool ControllerTracker::getAxisUp(size_t controller_index, size_t axis)
{
  if (controller_index >= controllers.size())
  {
    return false;
  }
  auto up =
    controllers[controller_index].new_data.axis[controllers[controller_index].axis_bindings[axis]] >=
    CONTROLLER::AXIS_DEADZONE;
  return up && controllers[controller_index]
                   .old_data.axis[controllers[controller_index].axis_bindings[axis]] <
                 CONTROLLER::AXIS_DEADZONE;
}
bool ControllerTracker::getAxisDown(size_t controller_index, size_t axis)
{
  if (controller_index >= controllers.size())
  {
    return false;
  }
  auto up =
    controllers[controller_index].new_data.axis[controllers[controller_index].axis_bindings[axis]] <=
    -CONTROLLER::AXIS_DEADZONE;
  return up && controllers[controller_index]
                   .old_data.axis[controllers[controller_index].axis_bindings[axis]] >
                 -CONTROLLER::AXIS_DEADZONE;
}
ASGE::Point2D ControllerTracker::getStick(size_t controller_index, size_t stick)
{
  if (controller_index >= controllers.size())
  {
    return ASGE::Point2D();
  }
  auto value = ASGE::Point2D(
    controllers[controller_index]
      .new_data.axis[controllers[controller_index].axis_bindings[stick * 2]],
    controllers[controller_index]
      .new_data.axis[controllers[controller_index].axis_bindings[stick * 2 + 1]]);
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
  controllers[controller_index].button_bindings = std::move(_button_bindings);
  controllers[controller_index].axis_bindings   = std::move(_axis_bindings);
}
int ControllerTracker::getLastButton(size_t controller_index)
{
  const auto& controller = input->getGamePad((controllers[controller_index].index));
  for (int i = 0; i < controller.no_of_buttons; i++)
  {
    if (
      static_cast<bool>(controller.buttons[i]) &&
      !controllers[controller_index].old_data.buttons[static_cast<size_t>(i)])
    {
      return i;
    }
  }
  return -1;
}
int ControllerTracker::getLastAxis(size_t controller_index)
{
  const auto& controller = input->getGamePad(controllers[controller_index].index);
  for (int i = 0; i < controller.no_of_axis; i++)
  {
    if (
      controller.axis[i] >= CONTROLLER::AXIS_DEADZONE * 2 &&
      std::fabs(controllers[controller_index].old_data.axis[static_cast<size_t>(i)]) <
        CONTROLLER::AXIS_DEADZONE * 2)
    {
      return i;
    }
  }
  return -1;
}
bool ControllerTracker::isConnected(size_t controller_index)
{
  if (controller_index >= controllers.size())
  {
    return false;
  }
  return input->getGamePad(controllers[controller_index].index).is_connected;
}
CONTROLLER::TrackedController::TrackedController(int _index) : index(_index)
{
  for (size_t i = 0; i < 14; i++)
  {
    button_bindings.insert(std::make_pair(i, i));
  }
  for (size_t i = 0; i < 6; i++)
  {
    axis_bindings.insert(std::make_pair(i, i));
  }
}
