//
// Created by hewis on 10/05/2021.
//

#ifndef ASGEMOVIEGAME_WEAPONDROP_H
#define ASGEMOVIEGAME_WEAPONDROP_H

#include "WeaponData.h"
#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
class WeaponDrop : public AnimatedSprite
{
 public:
  WeaponDrop(ASGE::Renderer* renderer, WeaponData weapon, ASGE::Point2D position = ASGE::Point2D());
  [[nodiscard]] WeaponData getWeapon();
  void playerInRange(bool yes);

 private:
  WeaponData data;
};

#endif // ASGEMOVIEGAME_WEAPONDROP_H
