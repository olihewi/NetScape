//
// Created by hewis on 10/05/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/Weapons/WeaponDrop.h"
WeaponDrop::WeaponDrop(
  ASGE::Renderer* renderer, WeaponData weapon, float _respawn_time, ASGE::Point2D position) :
  Sprite(renderer, weapon.sprite_floor),
  data(std::move(weapon)), respawn_time(_respawn_time)
{
  Sprite::dimensions(ASGE::Point2D(Sprite::getTextureSize().x / 2, Sprite::getTextureSize().y));
  Sprite::srcRect(
    0.1F, 0.1F, Sprite::getTextureSize().x / 2 - 0.2F, Sprite::getTextureSize().y - 0.2F);
  Sprite::centrePos(position);
}
WeaponData WeaponDrop::getWeapon()
{
  return data;
}
void WeaponDrop::playerInRange(bool yes)
{
  Sprite::srcRect(
    yes ? Sprite::getTextureSize().x / 2 + 0.1F : 0.1F,
    0.1F,
    Sprite::getTextureSize().x / 2 - 0.2F,
    Sprite::getTextureSize().y - 0.2F);
}
void WeaponDrop::update(InputTracker& /*input*/, float dt)
{
  if (respawn_timer > 0)
  {
    respawn_timer -= dt;
    if (respawn_timer <= 0)
    {
      visibility(true);
      respawn_timer = 0;
    }
  }
}
void WeaponDrop::setRespawnTimer()
{
  visibility(false);
  if (respawn_time > 0)
  {
    respawn_timer = respawn_time;
  }
}
float WeaponDrop::getRespawnTime() const
{
  return respawn_time;
}
