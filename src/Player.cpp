//
// Created by Bread on 08/04/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/Player.hpp"

#include "ASGEGameLib/Utilities/LineTrace.h"
#include <cmath>
#include <string>

Player::Player(
  ASGE::Renderer* renderer, const std::string& file_path, ASGE::Point2D _position,
  size_t control_id, SoLoud::Soloud* audio_engine) :
  AnimatedSprite(renderer, file_path, 20, _position),
  controller_id(control_id), weapon(audio_engine)
{
  // zOrder(1);
}

void Player::render(ASGE::Renderer* renderer)
{
  AnimatedSprite::render(renderer);
}

void Player::input(InputTracker& input, float dt)
{
  /// Movement
  auto left_stick = input.getControllerStick(controller_id, CONTROLLER::STICKS::LEFT);
  translate(ASGE::Point2D(left_stick.x * move_speed * dt, left_stick.y * move_speed * dt));
  /// Rotation
  auto right_stick = input.getControllerStick(controller_id, CONTROLLER::STICKS::RIGHT);
  if (std::hypotf(right_stick.x, right_stick.y) >= CONTROLLER::AXIS_DEADZONE)
  {
    rotation(std::atan2f(right_stick.y, right_stick.x));
  }
  /// move this shit to weapon
  if (input.getControllerAxisUp(controller_id, CONTROLLER::AXIS::RIGHT_TRIGGER))
  {
    weapon.fire();
  }
  if (input.getControllerButtonDown(controller_id, CONTROLLER::BUTTONS::X))
  {
    weapon.reload();
  }
}
void Player::fire()
{
  LineTrace(2, position(), rotation());
}
