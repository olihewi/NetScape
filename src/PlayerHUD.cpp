//
// Created by hewis on 08/05/2021.
//

#include "GameObjects/Player/HUD/PlayerHUD.h"
void PlayerHUD::update(InputTracker& input, float dt)
{
  for (auto& object : objects)
  {
    object->update(input, dt);
  }
  auto left_trigger = input.getControllerAxis(player.getID(), CONTROLLER::AXIS::LEFT_TRIGGER);
  lerped_focus      = lerped_focus + 8.F * dt * (left_trigger - lerped_focus);
  camera_shake      = ASGE::Point2D(
    camera_shake.x + 6.F * dt * (0 - camera_shake.x),
    camera_shake.y + 6.F * dt * (0 - camera_shake.y));
  if (player.getWeapon().hasFired())
  {
    cameraShake(ASGE::Point2D(
      -std::cos(player.getWeapon().rotation()) * 7.5F,
      -std::sin(player.getWeapon().rotation()) * 7.5F));
  }
}
void PlayerHUD::render(ASGE::Renderer* renderer)
{
  for (auto& object : objects)
  {
    object->render(renderer);
  }
}
void PlayerHUD::addObject(std::unique_ptr<GameObject> _object)
{
  objects.emplace_back(std::move(_object));
}
float PlayerHUD::getFocus() const
{
  return lerped_focus * player.getWeapon().getLookDistance();
}
PlayerHUD::PlayerHUD(Player& _player) : player(_player) {}
void PlayerHUD::cameraShake(ASGE::Point2D _shake)
{
  camera_shake = ASGE::Point2D(camera_shake.x + _shake.x, camera_shake.y + _shake.y);
}
ASGE::Point2D PlayerHUD::getCameraShake()
{
  return camera_shake;
}
