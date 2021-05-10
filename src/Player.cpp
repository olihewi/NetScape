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
  // zOrder(1);
  weapon.position(_position);
  player_walk.setLoop(true);
  player_walk.volume(0);
  player_walk.play();
}

void Player::render(ASGE::Renderer* renderer)
{
  AnimatedSprite::render(renderer);
  weapon.render(renderer);
}

void Player::input(InputTracker& input, float dt)
{
  weapon.update(input, dt);
  /// Movement
  auto left_stick        = input.getControllerStick(controller_id, CONTROLLER::STICKS::LEFT);
  float left_stick_hypot = std::hypot(left_stick.x, left_stick.y);
  if (left_stick_hypot > 1)
  {
    left_stick = ASGE::Point2D(left_stick.x / left_stick_hypot, left_stick.y / left_stick_hypot);
    left_stick_hypot = 1;
  }
  translate(ASGE::Point2D(left_stick.x * move_speed * dt, left_stick.y * move_speed * dt));
  if (left_stick_hypot >= CONTROLLER::AXIS_DEADZONE)
  {
    rotation(atan2f(left_stick.y, left_stick.x));
    setPlaybackSpeed(15 * left_stick_hypot);
    player_walk.volume(1);
  }
  else
  {
    player_walk.volume(0);
    setFrame(3);
  }
  player_walk.setSpeed(left_stick_hypot);
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
  has_been_hit       = true;
  has_been_hit_timer = 0;
  Logging::DEBUG("HIT");

  if (health <= 0)
  {
    is_dead = true;
    Sprite::visibility(false);
    weapon.visibility(false);
    Logging::DEBUG("DEAD");
  }
}
Weapon& Player::getWeapon()
{
  return weapon;
}
size_t Player::getID() const
{
  return controller_id;
}
void Player::update(InputTracker& input, float dt)
{
  // Logging::DEBUG("HAS BEEN HIT: " +std::to_string(static_cast<int>(has_been_hit)));

  weapon.colour(ASGE::Colour(playerR, playerG, playerB));
  if (has_been_hit)
  {
    playerG      = 0;
    playerB      = 0;
    has_been_hit = false;
  }
  else
  {
    if (playerB < 1)
    {
      float colour_gain = 1;
      playerG += colour_gain * (dt * 1.25F);
      playerB += colour_gain * (dt * 1.25F);
    }
  }

  AnimatedSprite::update(input, dt);
}
