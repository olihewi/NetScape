//
// Created by hewis on 12/04/2021.
//

#ifndef ASGEMOVIEGAME_CONTROLLERTRACKER_H
#define ASGEMOVIEGAME_CONTROLLERTRACKER_H
#include <Engine/Gamepad.hpp>
#include <Engine/Input.hpp>
#include <Engine/Point2D.hpp>
#include <array>
namespace CONTROLLER
{
  constexpr float AXIS_DEADZONE = 0.33F;
  namespace BUTTONS
  {
    constexpr int A              = 0;
    constexpr int B              = 1;
    constexpr int X              = 2;
    constexpr int Y              = 3;
    constexpr int LEFT_SHOULDER  = 4;
    constexpr int RIGHT_SHOULDER = 5;
    constexpr int BACK           = 6;
    constexpr int START          = 7;
    constexpr int LEFT_STICK     = 8;
    constexpr int RIGHT_STICK    = 9;
    constexpr int DPAD_UP        = 10;
    constexpr int DPAD_RIGHT     = 11;
    constexpr int DPAD_DOWN      = 12;
    constexpr int DPAD_LEFT      = 13;
  } // namespace BUTTONS
  namespace AXIS
  {
    constexpr int LEFT_STICK_X  = 0;
    constexpr int LEFT_STICK_Y  = 1;
    constexpr int RIGHT_STICK_X = 2;
    constexpr int RIGHT_STICK_Y = 3;
    constexpr int LEFT_TRIGGER  = 4;
    constexpr int RIGHT_TRIGGER = 5;
  } // namespace AXIS
  namespace STICKS
  {
    constexpr int LEFT  = 0;
    constexpr int RIGHT = 1;
  }
  struct LocalController
  {
   public:
    std::unordered_map<size_t, bool> buttons;
    std::unordered_map<size_t, float> axis;
  };
  struct TrackedController
  {
   public:
    explicit TrackedController(int _index);
    int index;
    LocalController old_data;
    LocalController new_data;
    std::unordered_map<size_t, size_t> button_bindings;
    std::unordered_map<size_t, size_t> axis_bindings;
  };
} // namespace CONTROLLER
class ControllerTracker
{
 public:
  explicit ControllerTracker(ASGE::Input* _input);
  void updateInput();

  [[nodiscard]] bool getButton(size_t controller_index, size_t button);
  [[nodiscard]] bool getButtonUp(size_t controller_index, size_t button);
  [[nodiscard]] bool getButtonDown(size_t controller_index, size_t button);

  [[nodiscard]] float getAxis(size_t controller_index, size_t axis);
  [[nodiscard]] bool getAxisUp(size_t controller_index, size_t axis);
  [[nodiscard]] bool getAxisDown(size_t controller_index, size_t axis);
  [[nodiscard]] ASGE::Point2D getStick(size_t controller_index, size_t stick);

  void setBinding(
    size_t controller_index, std::unordered_map<size_t, size_t> _button_bindings,
    std::unordered_map<size_t, size_t> _axis_bindings);
  [[nodiscard]] int getLastButton(size_t controller_index);
  [[nodiscard]] int getLastAxis(size_t controller_index);

  [[nodiscard]] bool isConnected(size_t controller_index);

 private:
  ASGE::Input* input;
  std::vector<CONTROLLER::TrackedController> controllers;
};

#endif // ASGEMOVIEGAME_CONTROLLERTRACKER_H
