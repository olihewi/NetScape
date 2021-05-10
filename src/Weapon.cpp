//
// Created by Bread on 19/04/2021.
//

#include "ASGEGameLib/GameObjects/Player/Weapons/Weapon.h"
#include <cmath>
Weapon::Weapon(ASGE::Renderer* renderer, SoLoud::Soloud* audio_engine, size_t _player_id) :
  AnimatedSprite(renderer, "data/images/player/pistol.png", 0), bullet(renderer),
  current_ammo(max_ammo),
  sounds(std::array<Sound, 3>{ Sound(audio_engine, "data/audio/guns/pistol/fire.wav"),
                               Sound(audio_engine, "data/audio/guns/pistol/empty.wav"),
                               Sound(audio_engine, "data/audio/guns/pistol/reload.wav") }),
  player_id(_player_id),
  ammo_reserve(40)
{
  // zOrder(2);
}

void Weapon::render(ASGE::Renderer* renderer)
{
  AnimatedSprite::render(renderer);
  bullet.render(renderer);
}
void Weapon::fire()
{
  if (current_ammo > 0)
  {
    ASGE::Point2D muzzle;
    muzzle.x = AnimatedSprite::position().x - 10;
    muzzle.y = AnimatedSprite::position().y + 10;
    current_ammo--;
    fire_timer = fire_rate;
    sounds[0].play();
    bullet.hitCheck(250, muzzle, AnimatedSprite::rotation());
  }
  else
  {
    sounds[1].play();
    fire_timer = fire_rate;
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
    rotation(atan2f(right_stick.y, right_stick.x));
  }
  /// Firing
  if (is_automatic)
  {
    if (
      input.getControllerButton(player_id, CONTROLLER::BUTTONS::RIGHT_SHOULDER) ||
      input.getControllerAxis(player_id, CONTROLLER::AXIS::RIGHT_TRIGGER) >
        CONTROLLER::AXIS_DEADZONE)
    {
      if (fire_timer <= 0 && reload_timer <= 0)
      {
        fire();
      }
    }
  }
  else
  {
    if (
      input.getControllerButtonDown(player_id, CONTROLLER::BUTTONS::RIGHT_SHOULDER) ||
      input.getControllerAxisUp(player_id, CONTROLLER::AXIS::RIGHT_TRIGGER))
    {
      if (fire_timer <= 0 && reload_timer <= 0)
      {
        fire();
      }
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
      1 + static_cast<size_t>(
            ((fire_rate - fire_timer) / fire_rate * static_cast<float>(fire_frames))));
  }
  else if (reload_timer > 0)
  {
    reload_timer -= dt;
    setFrame(
      1 + fire_frames +
      static_cast<size_t>(
        ((reload_time - reload_timer) / reload_time * static_cast<float>(reload_frames))));
  }
  else
  {
    setFrame(0);
  }
  bullet.update(dt);
}

int Weapon::getAmmoReserves()
{
  return ammo_reserve;
}
