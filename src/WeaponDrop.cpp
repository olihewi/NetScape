//
// Created by hewis on 10/05/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/Weapons/WeaponDrop.h"
WeaponDrop::WeaponDrop(ASGE::Renderer* renderer, WeaponData weapon, ASGE::Point2D position) :
  Sprite(renderer, weapon.sprite_floor, position), data(std::move(weapon))
{
  Sprite::dimensions(ASGE::Point2D(Sprite::getTextureSize().x / 2, Sprite::getTextureSize().y));
  Sprite::srcRect(
    0.1F, 0.1F, Sprite::getTextureSize().x / 2 - 0.2F, Sprite::getTextureSize().y - 0.2F);
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
