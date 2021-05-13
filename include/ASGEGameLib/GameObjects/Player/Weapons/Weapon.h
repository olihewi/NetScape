//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_WEAPON_H
#define ASGEMOVIEGAME_WEAPON_H

#include "WeaponData.h"
#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
#include <ASGEGameLib/Utilities/LineTrace.h>
#include <ASGEGameLib/Utilities/Sound.h>
#include <random>
class Weapon : public AnimatedSprite
{
 public:
  Weapon(
    ASGE::Renderer* renderer, SoLoud::Soloud* audio_engine, size_t _player_id,
    WeaponData* _weapon_data);
  void update(InputTracker& input, float dt) override;
  void fire();
  void reload();
  [[nodiscard]] int getAmmoReserves() const;
  [[nodiscard]] float getLookDistance() const;
  void render(ASGE::Renderer* renderer) override;
  [[nodiscard]] bool hasFired() const;
  void setWeapon(ASGE::Renderer* renderer, WeaponData* _weapon_data);
  [[nodiscard]] WeaponData* getWeaponData();
  [[nodiscard]] int getCurrentAmmo() const;
  void trace(ASGE::Point2D origin, ASGE::Point2D end, size_t index = 0);

 private:
  WeaponData* weapon_data;
  std::array<Sound, 4> sounds;
  size_t player_id;
  std::vector<LineTrace> bullets;

  /// Current Stats
  int current_ammo;
  int ammo_reserve;
  float fire_timer         = 0;
  float reload_timer       = 0;
  float current_inaccuracy = 0;
  bool has_fired           = false;
  float last_safe_rotation = 0;

  /// Random Number Generator
  std::default_random_engine el;
  std::uniform_real_distribution<float> random_num;
};

#endif // ASGEMOVIEGAME_WEAPON_H
