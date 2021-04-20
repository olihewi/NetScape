//
// Created by Bread on 19/04/2021.
//

#include "ASGEGameLib/GameObjects/Player/Weapons/Weapon.h"
Weapon::Weapon(SoLoud::Soloud* audio_engine) :
  sounds(std::array<Sound, 3>{ Sound(audio_engine, "data/audio/guns/pistol/fire.wav"),
                               Sound(audio_engine, "data/audio/guns/pistol/empty.wav"),
                               Sound(audio_engine, "data/audio/guns/pistol/reload.wav") })
{
}
void Weapon::fire()
{
  sounds[0].play();
}
void Weapon::reload()
{
  sounds[2].play();
}
