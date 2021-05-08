//
// Created by Bread on 08/04/2021.
//

#include "../include/ASGEGameLib/GameObjects/Player/Player.hpp"
#include "Engine/Logger.hpp"
#include <Utilities/FontManager.h>
#include <cmath>

Player::Player(
  ASGE::Renderer* renderer, ASGE::Point2D _position, size_t control_id,
  SoLoud::Soloud* audio_engine) :
  AnimatedSprite(renderer, "data/images/player/legs.png", 15, _position),
  controller_id(control_id), weapon(renderer, audio_engine, controller_id),
  player_walk(audio_engine, "data/audio/player_walk.wav")
{
  zOrder(1);
  weapon.position(_position);
}

void Player::render(ASGE::Renderer* renderer)
{
  AnimatedSprite::render(renderer);
  weapon.render(renderer);
}

void Player::input(InputTracker& input, float dt)
{
  weapon.update(input, dt);
  AnimatedSprite::update(input, dt);
  /// Movement
  auto left_stick = input.getControllerStick(controller_id, CONTROLLER::STICKS::LEFT);
  translate(ASGE::Point2D(left_stick.x * move_speed * dt, left_stick.y * move_speed * dt));
  auto left_stick_hypot = std::hypotf(left_stick.x, left_stick.y);
  if (left_stick_hypot >= CONTROLLER::AXIS_DEADZONE)
  {
    rotation(atan2f(left_stick.y, left_stick.x));
    setPlaybackSpeed(15 * left_stick_hypot);
    //player_walk.getSound().NO_ATTENUATION;
    player_walk.getSound().setSingleInstance(true);
    player_walk.play();
  }
  else
  {
    setFrame(3);
    player_walk.stop();
  }


}
void Player::position(ASGE::Point2D _position)
{
  Sprite::position(_position);
  weapon.position(_position);
}
void Player::translate(ASGE::Point2D _translation)
{
  Sprite::translate(_translation);
  weapon.translate(_translation);
}
void Player::takeDamage(float damage)
{
  health -= damage;
  Logging::DEBUG("HIT");
  if (health <= 0)
  {
    is_dead = true;
    Sprite::visibility(false);
    weapon.visibility(false);
    Logging::DEBUG("DEAD");
  }

  /// Health
  //playerHealth.adjustPlayerHealth(health);
}
 Weapon& Player::getWeapon()
{
  return weapon;
}
