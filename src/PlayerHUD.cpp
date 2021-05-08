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
