//
// Created by Bread on 08/04/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/Player.hpp"

#include "ASGEGameLib/Utilities/LineTrace.h"
#include <cmath>
#include <string>

Player::Player(
  ASGE::Renderer* renderer, ASGE::Point2D _position, size_t control_id,
  SoLoud::Soloud* audio_engine) :
  AnimatedSprite(renderer, "data/images/player/legs.png", 15, _position),
  controller_id(control_id), weapon(renderer, audio_engine, controller_id)
{
  // zOrder(1);
  weapon.position(_position);
}

void Player::render(ASGE::Renderer* renderer)
{
  AnimatedSprite::render(renderer);
  weapon.render(renderer);
}

void Player::input(InputTracker& input, float dt)
{
  AnimatedSprite::update(input, dt);
  /// Movement
  auto left_stick = input.getControllerStick(controller_id, CONTROLLER::STICKS::LEFT);
  translate(ASGE::Point2D(left_stick.x * move_speed * dt, left_stick.y * move_speed * dt));
  if (std::hypotf(left_stick.x, left_stick.y) >= CONTROLLER::AXIS_DEADZONE)
  {
    rotation(std::atan2f(left_stick.y, left_stick.x));
  }
  else
  {
    setFrame(3);
  }
  weapon.update(input, dt);
}
void Player::fire()
{
  LineTrace(2, AnimatedSprite::position(), rotation());
}
void Player::position(ASGE::Point2D _position)
{
  Sprite::position(_position);
  weapon.position(_position);
}
void Player::translate(ASGE::Point2D _translation)
{
  Sprite::translate(_translation);
  weapon.translate(_translation);
}
