//
// Created by hewis on 10/05/2021.
//

#ifndef ASGEMOVIEGAME_WEAPONDATA_H
#define ASGEMOVIEGAME_WEAPONDATA_H

struct WeaponData
{
 public:
  WeaponData() = default;
  /// Sprites
  std::string sprite_held  = "data/images/player/pistol.png";
  std::string sprite_floor = "data/images/player/pistol_bullet.png"; // change
  /// Audio
  std::string sfx_fire   = "data/audio/guns/pistol/fire.wav";
  std::string sfx_reload = "data/audio/guns/pistol/reload.wav";
  std::string sfx_empty  = "data/audio/guns/pistol/empty.wav";
  /// Stats
  bool is_automatic   = true;
  int max_ammo        = 10;
  int ammo_reserve    = 40;
  float fire_rate     = 0.2F;
  float reload_time   = 0.75F;
  float recoil        = 0.2F;
  float recoil_regain = 0.6F;
  float inaccuracy    = 0.F;
  float look_distance = 1.F;
  /// Animation Data
  size_t fire_frames   = 1;
  size_t reload_frames = 6;
};
#endif // ASGEMOVIEGAME_WEAPONDATA_H
