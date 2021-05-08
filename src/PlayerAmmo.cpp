//
// Created by Work on 08/05/2021.
//

#include "ASGEGameLib/GameObjects/Player/HUD/PlayerAmmo.hpp"

PlayerAmmo::PlayerAmmo(ASGE::Renderer* renderer, Weapon& _weapon, Player& _player) :
  player(_player),
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
      (player.AnimatedSprite::position().x - 16*5)
       + static_cast<float>(i) * bullet[i].dimensions().x,
      player.AnimatedSprite::position().y - 105));
    bullet[i].zOrder(0);
  }
}

void PlayerAmmo::render(ASGE::Renderer* renderer)
{
  for (int i = 0; i < weapon.current_ammo; ++i)
  {
    bullet[i].Sprite::render(renderer);
  }

}
