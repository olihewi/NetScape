//
// Created by Work on 08/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerAmmo.hpp"
#include <Engine/Logger.hpp>
PlayerAmmo::PlayerAmmo(
  ASGE::Renderer* renderer, Weapon& _weapon, Player& _player, float x, float y) :
  weapon(_weapon),
  player(_player),
  bullet(std::array<Sprite, 10>{
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)),
    Sprite(renderer, "data/images/player/pistol_bullet.png", ASGE::Point2D(0, 0)) }),
  posX(x), posY(y),
  AmmoReserve(_weapon.getAmmoReserves()),
  AmmoReserveDisplay(renderer, std::to_string(player.getWeapon().getAmmoReserves()) + "x", ASGE::Point2D(0,0))
{
  posX -= bullet[0].dimensions().x * (static_cast<float>(weapon.max_ammo) / 2);
  for (size_t i = 0; i < static_cast<size_t>(weapon.max_ammo); ++i)
  {
    bullet[i].position(
      ASGE::Point2D((posX + static_cast<float>(i) * bullet[i].dimensions().x), posY));
  }
  AmmoReserveDisplay.position(ASGE::Point2D(bullet[0].position().x - 35,
                                                    bullet[0].position().y + bullet[0].dimensions().y));
}

void PlayerAmmo::update(InputTracker& input, float dt)
{
  
  GameObject::update(input, dt);
  AmmoReserveDisplay.contents(std::to_string(weapon.getAmmoReserves()) + "x");

}

void PlayerAmmo::render(ASGE::Renderer* renderer)
{
  if (player.health > 0)
  {
    for (size_t i = 0; i < static_cast<size_t>(weapon.current_ammo); ++i)
    {
      bullet[i].Sprite::render(renderer);
    }
  }

  AmmoReserveDisplay.render(renderer);

}
