//
// Created by Bread on 08/04/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/Player.hpp"

#include <cmath>

Player::Player(
  ASGE::Renderer* renderer, const std::string& file_path, ASGE::Point2D _position,
  ASGE::Point2D _dimensions, size_t playback_speed, short z_order, int control_id) : AnimatedSprite(renderer, file_path, 10, _position)
{
  controller_id = control_id;
}

void Player::render(ASGE::Renderer* renderer)
{
  AnimatedSprite::render(renderer);
}

void Player::input(InputTracker& input, float dt)
{
  if(input.getControllerAxis(controller_id, 0) != 0)
  {
    if(input.getControllerAxis(controller_id, 1) != 0)
    {
      translate(input.getControllerStick(controller_id, 0));
    }
  }

  if(input.getControllerAxis(controller_id, 2) != 0)
  {
    if(input.getControllerAxis(controller_id, 3) != 0)
    {
      rotation(atan2(input.getControllerAxis(controller_id, 3), input.getControllerAxis(controller_id, 2)));
    }
  }

}

