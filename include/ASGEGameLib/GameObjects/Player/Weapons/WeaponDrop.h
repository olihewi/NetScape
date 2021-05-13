//
// Created by hewis on 10/05/2021.
//

#ifndef ASGEMOVIEGAME_WEAPONDROP_H
#define ASGEMOVIEGAME_WEAPONDROP_H

#include "WeaponData.h"
#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
class WeaponDrop : public Sprite
{
 public:
  WeaponDrop(
    ASGE::Renderer* renderer, WeaponData* weapon, float _respawn_time,
    ASGE::Point2D position = ASGE::Point2D());
  [[nodiscard]] WeaponData* getWeapon();
  void playerInRange(bool yes);
  void update(InputTracker& input, float dt) override;
  void setRespawnTimer();
  [[nodiscard]] float getRespawnTime() const;

 private:
  WeaponData* data;
  float respawn_time;
  float respawn_timer = 0;
};

#endif // ASGEMOVIEGAME_WEAPONDROP_H
