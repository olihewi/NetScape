//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_WEAPON_H
#define ASGEMOVIEGAME_WEAPON_H

#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
#include <ASGEGameLib/Utilities/LineTrace.h>
#include <ASGEGameLib/Utilities/Sound.h>
#include <random>
class Weapon : public AnimatedSprite
{
 public:
  Weapon(ASGE::Renderer* renderer, SoLoud::Soloud* audio_engine, size_t _player_id);
  void update(InputTracker& input, float dt) override;
  void fire();
  void reload();
  [[nodiscard]] int getAmmoReserves() const;
  void render(ASGE::Renderer* renderer) override;

  LineTrace bullet;

  int max_ammo = 10;
  int current_ammo;

 private:
  std::array<Sound, 3> sounds;
  size_t player_id;

  /// Weapon Stats
  bool is_automatic = true;

  float fire_rate   = 0.2F;
  float reload_time = 0.75F;

  float recoil        = 0.2F;
  float recoil_regain = 0.6F;

  /// Current Stats

  int ammo_reserve;
  float fire_timer         = 0;
  float reload_timer       = 0;
  float current_inaccuracy = 0;

  /// Animation Data
  size_t fire_frames   = 1;
  size_t reload_frames = 6;

  /// Random Number Generator
  std::random_device r;
  std::default_random_engine el;
  std::uniform_real_distribution<float> random_num;
};

#endif // ASGEMOVIEGAME_WEAPON_H
