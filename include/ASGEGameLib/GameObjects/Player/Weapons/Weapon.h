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
    ASGE::Renderer* renderer, SoLoud::Soloud* audio_engine, size_t _player_id, WeaponData _weapon);
  void update(InputTracker& input, float dt) override;
  void fire();
  void reload();
  [[nodiscard]] int getAmmoReserves() const;
  [[nodiscard]] float getLookDistance() const;
  void render(ASGE::Renderer* renderer) override;
  [[nodiscard]] bool hasFired() const;
  void setWeapon(ASGE::Renderer* renderer, SoLoud::Soloud* engine, const WeaponData& _weapon);
  [[nodiscard]] WeaponData& getWeaponData();
  [[nodiscard]] int getCurrentAmmo() const;

  LineTrace bullet;

 private:
  std::array<Sound, 3> sounds;
  size_t player_id;

  /// Weapon Stats
  WeaponData weapon_data;

  /// Current Stats
  int current_ammo;
  int ammo_reserve;
  float fire_timer         = 0;
  float reload_timer       = 0;
  float current_inaccuracy = 0;
  bool has_fired           = false;

  /// Random Number Generator
  std::random_device r;
  std::default_random_engine el;
  std::uniform_real_distribution<float> random_num;
};

#endif // ASGEMOVIEGAME_WEAPON_H
