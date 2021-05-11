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
  controller_id(control_id), weapon(renderer, audio_engine, controller_id, WeaponData()),
  player_walk(audio_engine, "data/audio/player_walk.wav"), lives(3),
  player_damaged(audio_engine, "data/audio/damaged.wav"),
  player_killed(audio_engine, "data/audio/wilhelm.wav")
{
  // zOrder(1);
  weapon.position(_position);
  player_walk.setLoop(true);
  player_walk.volume(0);
  player_walk.play();
  player_damaged.volume(5);
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
  auto left_stick           = input.getControllerStick(controller_id, CONTROLLER::STICKS::LEFT);
  float left_stick_hypot    = std::hypot(left_stick.x, left_stick.y);
  auto sprint_button        = input.getControllerButton(controller_id, CONTROLLER::BUTTONS::B);
  auto score_readout_button = input.getControllerButtonDown(controller_id, CONTROLLER::BUTTONS::X);
  if (left_stick_hypot > 1)
  {
    left_stick = ASGE::Point2D(left_stick.x / left_stick_hypot, left_stick.y / left_stick_hypot);
    left_stick_hypot = 1;
  }
  float movespeed = move_speed * (sprint_button ? 2.F : 1.F);
  translate(ASGE::Point2D(left_stick.x, left_stick.y) * movespeed * dt);
  if (left_stick_hypot >= CONTROLLER::AXIS_DEADZONE)
  {
    rotation(atan2f(left_stick.y, left_stick.x));
    setPlaybackSpeed(15 * left_stick_hypot * movespeed / move_speed);
    player_walk.volume(1);
  }
  else
  {
    player_walk.volume(0);
    setFrame(3);
  }
  player_walk.setSpeed(left_stick_hypot * movespeed / move_speed);
  if (is_dead)
  {
    player_walk.volume(0);
  }

  if (score_readout_button)
  {
    Logging::DEBUG(
      "Player: " + std::to_string(controller_id + 1) + "\nkills: " + std::to_string(score.kills) +
      "\ndeaths: " + std::to_string(score.deaths) + "\nmisses: " + std::to_string(score.miss) +
      "\nhits: " + std::to_string(score.hit) +
      "\naccuracy: " + std::to_string((score.hit / (score.hit + score.miss)) * 100));
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
  has_been_hit       = true;
  has_been_hit_timer = 0;
  if (!is_dead)
  {
    player_damaged.play();
  }

  Logging::DEBUG("HIT");
  if (health <= 0)
  {
    is_dead = true;
    score.deaths++;
    Sprite::visibility(false);
    weapon.visibility(false);
    player_killed.play();
    // Logging::DEBUG("DEAD");
  }
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
      playerG += colour_gain * (dt);
      playerB += colour_gain * (dt);
    }
  }

  AnimatedSprite::update(input, dt);
}

/// GETTERS AND SETTERS LIST

Weapon& Player::getWeapon()
{
  return weapon;
}

float Player::getMaxHealth() const
{
  return max_health;
}

float Player::getHealth() const
{
  return health;
}
void Player::setHealth(float _health)
{
  health = _health;
}

int Player::getMaxLives() const
{
  return max_lives;
}
int Player::getLives() const
{
  return lives;
}
void Player::setLives(int _lives)
{
  lives = _lives;
}

ASGE::Point2D Player::getSpawnPoint()
{
  return spawn_point;
}
void Player::setSpawnPoint(ASGE::Point2D _spawn_point)
{
  spawn_point = _spawn_point;
}

Score& Player::getScore()
{
  return score;
}
