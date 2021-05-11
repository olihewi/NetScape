//
// Created by hewis on 10/05/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/Weapons/WeaponDrop.h"
WeaponDrop::WeaponDrop(ASGE::Renderer* renderer, WeaponData weapon, ASGE::Point2D position) :
  AnimatedSprite(renderer, weapon.sprite_floor, 0, position), data(std::move(weapon))
{
}
WeaponData WeaponDrop::getWeapon()
{
  return data;
}
void WeaponDrop::playerInRange(bool yes)
{
  AnimatedSprite::setFrame(yes ? 1 : 0);
}
