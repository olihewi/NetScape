//
// Created by Bread on 19/04/2021.
//

#include "ASGEGameLib/GameObjects/Player/Weapons/Weapon.h"
Weapon::Weapon(ASGE::Renderer* renderer, SoLoud::Soloud* audio_engine, size_t _player_id) :
  AnimatedSprite(renderer, "data/images/player/pistol.png", 0),
  sounds(std::array<Sound, 3>{ Sound(audio_engine, "data/audio/guns/pistol/fire.wav"),
                               Sound(audio_engine, "data/audio/guns/pistol/empty.wav"),
                               Sound(audio_engine, "data/audio/guns/pistol/reload.wav") }),
  player_id(_player_id)
{
  current_ammo = max_ammo;
  ammo_reserve = max_ammo * 4;
}
void Weapon::fire()
{
  if (current_ammo > 0)
  {
    current_ammo--;
    fire_timer = fire_rate;
    sounds[0].play();
  }
  else
  {
    sounds[1].play();
  }
}
void Weapon::reload()
{
  for (int i = current_ammo; i < max_ammo; i++)
  {
    if (ammo_reserve <= 0)
    {
      break;
    }
    ammo_reserve--;
    current_ammo++;
    reload_timer = reload_time;
    sounds[2].play();
  }
}
void Weapon::update(InputTracker& input, float dt)
{
  /// Rotating
  auto right_stick = input.getControllerStick(player_id, CONTROLLER::STICKS::RIGHT);
  if (std::hypotf(right_stick.x, right_stick.y) >= CONTROLLER::AXIS_DEADZONE)
  {
    rotation(std::atan2f(right_stick.y, right_stick.x));
  }
  /// Firing
  if (
    input.getControllerButtonDown(player_id, CONTROLLER::BUTTONS::RIGHT_SHOULDER) ||
    input.getControllerAxisUp(player_id, CONTROLLER::AXIS::RIGHT_TRIGGER))
  {
    if (fire_timer <= 0 && reload_timer <= 0)
    {
      fire();
    }
  }
  /// Reloading
  if (input.getControllerButtonDown(player_id, CONTROLLER::BUTTONS::X))
  {
    if (current_ammo < max_ammo && fire_timer <= 0 && reload_timer <= 0)
    {
      reload();
    }
  }
  if (fire_timer > 0)
  {
    fire_timer -= dt;
    setFrame(
      1 +
      static_cast<int>(((fire_rate - fire_timer) / fire_rate * static_cast<float>(fire_frames))));
  }
  else if (reload_timer > 0)
  {
    reload_timer -= dt;
    setFrame(
      1 + fire_frames +
      static_cast<int>(
        ((reload_time - reload_timer) / reload_time * static_cast<float>(reload_frames))));
  }
  else
  {
    setFrame(0);
  }
}
