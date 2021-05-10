//
// Created by hewis on 10/05/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/HUD/Crosshair.h"
Crosshair::Crosshair(ASGE::Renderer* renderer, size_t _player_id) :
  Sprite(renderer, "data/images/player/crosshair.png"), player_id(_player_id)
{
  dimensions(ASGE::Point2D(32 * 1.5F, 32 * 1.5F));
  zOrder(10);
}
void Crosshair::update(InputTracker& input, float /*dt*/)
{
  auto right_stick = input.getControllerStick(player_id, CONTROLLER::STICKS::RIGHT);
  auto mag         = std::hypot(right_stick.x, right_stick.y);
  auto screen      = ASGE::Point2D(
    static_cast<float>(ASGE::SETTINGS.window_width) / 4,
    static_cast<float>(ASGE::SETTINGS.window_height) / 4);
  opacity(mag);
  centrePos(ASGE::Point2D(screen.x + right_stick.x * 300, screen.y + right_stick.y * 300));
}
