//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_WEAPON_H
#define ASGEMOVIEGAME_WEAPON_H

#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
#include <ASGEGameLib/Utilities/Sound.h>
#include <ASGEGameLib/Utilities/LineTrace.h>
class Weapon : public AnimatedSprite
{
 public:
  Weapon(ASGE::Renderer* renderer, SoLoud::Soloud* audio_engine, size_t _player_id);
  void update(InputTracker& input, float dt) override;
  void fire();
  void reload();
  void render(ASGE::Renderer* renderer);

  LineTrace bullet;

 private:
  std::array<Sound, 3> sounds;
  size_t player_id;


  /// Weapon Stats
  int max_ammo      = 10;
  float fire_rate   = 0.2F;
  float reload_time = 0.75F;

  /// Current Stats
  int current_ammo;
  int ammo_reserve;
  float fire_timer   = 0;
  float reload_timer = 0;

  /// Animation Data
  size_t fire_frames   = 1;
  size_t reload_frames = 6;
};

#endif // ASGEMOVIEGAME_WEAPON_H
