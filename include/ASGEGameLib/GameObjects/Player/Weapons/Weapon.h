//
// Created by Bread on 19/04/2021.
//

#ifndef ASGEMOVIEGAME_WEAPON_H
#define ASGEMOVIEGAME_WEAPON_H

#include <ASGEGameLib/GameObjects/GameObject.h>
#include <ASGEGameLib/Utilities/Sound.h>
class Weapon : public GameObject
{
 public:
  explicit Weapon(SoLoud::Soloud* audio_engine);
  void fire();
  void reload();

 private:
  std::array<Sound, 3> sounds;
};

#endif // ASGEMOVIEGAME_WEAPON_H
