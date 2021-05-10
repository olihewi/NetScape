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
  auto left_trigger = input.getControllerAxis(index, CONTROLLER::AXIS::LEFT_TRIGGER);
  lerped_focus      = lerped_focus + 0.5F * (left_trigger - lerped_focus);
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
  return lerped_focus;
}
PlayerHUD::PlayerHUD(size_t _index) : index(_index) {}
