//
// Created by Work on 08/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerAmmo.hpp"
#include <Engine/Logger.hpp>
PlayerAmmo::PlayerAmmo(ASGE::Renderer* renderer, Weapon& _weapon) :
  weapon(_weapon),
  bullet(std::array<Sprite, 10>{
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png",ASGE::Point2D(0,0))})
{
}

void PlayerAmmo::update(InputTracker& input, float dt)
{

  GameObject::update(input, dt);

  for (int i = 0; i < weapon.max_ammo; ++i)
  {
    bullet[i].position(ASGE::Point2D(
      static_cast<float>(i) * bullet[i].dimensions().x,
      0));
    Logging::DEBUG("bullet " + std::to_string(i) + " x pos: " + std::to_string( bullet[i].position().x));
    bullet[i].zOrder(0);
  }
}

void PlayerAmmo::render(ASGE::Renderer* renderer)
{
  for (int i = 0; i < weapon.max_ammo; ++i)
  {
    bullet[i].Sprite::render(renderer);
  }
}