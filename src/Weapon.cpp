//
// Created by Bread on 19/04/2021.
//

#include "ASGEGameLib/GameObjects/Player/Weapons/Weapon.h"
#include <cmath>
Weapon::Weapon(
  ASGE::Renderer* renderer, SoLoud::Soloud* audio_engine, size_t _player_id,
  WeaponData* _weapon_data) :
  AnimatedSprite(renderer, _weapon_data->sprite_held, 0),
  weapon_data(_weapon_data),
  sounds(std::array<Sound, 4>{ Sound(audio_engine, weapon_data->sfx_fire),
                               Sound(audio_engine, weapon_data->sfx_empty),
                               Sound(audio_engine, weapon_data->sfx_reload),
                               Sound(audio_engine, weapon_data->sfx_pickup) }),
  player_id(_player_id), current_ammo(weapon_data->max_ammo),
  ammo_reserve(weapon_data->ammo_reserve), el(std::random_device{}()), random_num(-1.F, 1.F)
{
  // zOrder(2);
  for (int i = 0; i < weapon_data->num_bullets; i++)
  {
    bullets.emplace_back(LineTrace(renderer));
  }
}

void Weapon::render(ASGE::Renderer* renderer)
{
  AnimatedSprite::render(renderer);
  for (auto& bullet : bullets)
  {
    bullet.render(renderer);
  }
}
void Weapon::fire()
{
  if (fire_timer > 0 || reload_timer > 0)
  {
    return;
  }
  if (current_ammo > 0)
  {
    ASGE::Point2D muzzle;
    muzzle.x = AnimatedSprite::position().x - 10;
    muzzle.y = AnimatedSprite::position().y + 10;
    current_ammo--;
    fire_timer = weapon_data->fire_rate;
    sounds[0].play();
    if (weapon_data->num_bullets == 1)
    {
      float bullet_dir = random_num(el) * current_inaccuracy + AnimatedSprite::rotation();
      rotation(bullet_dir);
    }
    last_safe_rotation = rotation();
    current_inaccuracy += weapon_data->recoil;
    has_fired = true;
  }
  else
  {
    sounds[1].play();
    fire_timer = weapon_data->fire_rate;
  }
}
void Weapon::reload()
{
  if (current_ammo < weapon_data->max_ammo && fire_timer <= 0 && reload_timer <= 0 && ammo_reserve > 0)
  {
    int ammo_gain = current_ammo;
    current_ammo  = static_cast<int>(std::fmin(current_ammo + ammo_reserve, weapon_data->max_ammo));
    ammo_gain     = current_ammo - ammo_gain;
    ammo_reserve  = static_cast<int>(std::fmax(ammo_reserve - ammo_gain, 0));
    reload_timer  = weapon_data->reload_time;
    sounds[2].play();
  }
}
void Weapon::update(InputTracker& input, float dt)
{
  has_fired = false;
  /// Rotating
  auto right_stick = input.getControllerStick(player_id, CONTROLLER::STICKS::RIGHT);
  if (
    std::hypotf(right_stick.x, right_stick.y) >= CONTROLLER::AXIS_DEADZONE &&
    fire_timer <= weapon_data->fire_rate / 2)
  {
    rotation(atan2f(right_stick.y, right_stick.x));
  }
  /// Firing
  if (weapon_data->is_automatic)
  {
    if (
      input.getControllerButton(player_id, CONTROLLER::BUTTONS::RIGHT_SHOULDER) ||
      input.getControllerAxis(player_id, CONTROLLER::AXIS::RIGHT_TRIGGER) >
        CONTROLLER::AXIS_DEADZONE)
    {
      fire();
    }
  }
  else
  {
    if (
      input.getControllerButtonDown(player_id, CONTROLLER::BUTTONS::RIGHT_SHOULDER) ||
      input.getControllerAxisUp(player_id, CONTROLLER::AXIS::RIGHT_TRIGGER))
    {
      fire();
    }
  }

  /// Reloading
  if (input.getControllerButtonDown(player_id, CONTROLLER::BUTTONS::X))
  {
    reload();
  }
  if (fire_timer > 0)
  {
    fire_timer -= dt;
    setFrame(
      1 + static_cast<size_t>(
            ((weapon_data->fire_rate - fire_timer) / weapon_data->fire_rate *
             static_cast<float>(weapon_data->fire_frames))));
  }
  else if (reload_timer > 0)
  {
    reload_timer -= dt;
    setFrame(
      1 + weapon_data->fire_frames +
      static_cast<size_t>(
        ((weapon_data->reload_time - reload_timer) / weapon_data->reload_time *
         static_cast<float>(weapon_data->reload_frames))));
  }
  else
  {
    setFrame(0);
  }
  if (current_inaccuracy > weapon_data->inaccuracy)
  {
    current_inaccuracy =
      fmax(current_inaccuracy - weapon_data->recoil_regain * dt, weapon_data->inaccuracy);
  }
  for (auto& bullet : bullets)
  {
    bullet.update(dt);
  }
}

int Weapon::getAmmoReserves() const
{
  return ammo_reserve;
}
float Weapon::getLookDistance() const
{
  return weapon_data->look_distance;
}
bool Weapon::hasFired() const
{
  return has_fired;
}
WeaponData* Weapon::getWeaponData()
{
  return weapon_data;
}
int Weapon::getCurrentAmmo() const
{
  return current_ammo;
}
void Weapon::trace(ASGE::Point2D origin, ASGE::Point2D end, size_t index)
{
  rotation(last_safe_rotation);
  float falloff = origin.distance(end) / weapon_data->range * weapon_data->range_falloff;
  bullets[index].setLine(origin, end, 0.1F, 3, falloff);
  if (static_cast<int>(index) < weapon_data->num_bullets - 1)
  {
    float bullet_dir = random_num(el) * weapon_data->inaccuracy + AnimatedSprite::rotation();
    rotation(bullet_dir);
  }
}
void Weapon::setWeapon(ASGE::Renderer* renderer, WeaponData* _weapon_data)
{
  weapon_data = _weapon_data;
  AnimatedSprite::loadAnimation(renderer, weapon_data->sprite_held, 0);
  sounds[0].setSound(weapon_data->sfx_fire);
  sounds[1].setSound(weapon_data->sfx_empty);
  sounds[2].setSound(weapon_data->sfx_reload);
  sounds[3].setSound(weapon_data->sfx_pickup);
  current_ammo       = weapon_data->max_ammo;
  ammo_reserve       = weapon_data->ammo_reserve;
  current_inaccuracy = weapon_data->inaccuracy;
  sounds[3].play();
  bullets.clear();
  for (int i = 0; i < weapon_data->num_bullets; i++)
  {
    bullets.emplace_back(LineTrace(renderer));
  }
}
