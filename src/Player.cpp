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
  player_killed(audio_engine, "data/audio/wilhelm.wav"),
  invis_recharged(audio_engine, "data/audio/solo_beeps_24.wav")
{
  // zOrder(1);
  weapon.position(_position);
  player_walk.setLoop(true);
  player_walk.volume(0);
  player_walk.play();
  player_damaged.volume(5);

  invis_recharged.volume(0.2F);
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
  auto sprint_button        = input.getControllerButton(controller_id, CONTROLLER::BUTTONS::LEFT_STICK);
  auto score_readout_button = input.getControllerButtonDown(controller_id, CONTROLLER::BUTTONS::X);
  auto invis_button         = input.getControllerButtonDown(controller_id, CONTROLLER::BUTTONS::DPAD_LEFT);
  auto dash_button          = input.getControllerButtonDown(controller_id, CONTROLLER::BUTTONS::B);
  auto heal_button          = input.getControllerButtonDown(controller_id, CONTROLLER::BUTTONS::DPAD_RIGHT);

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

  if (invis_button && invis_cooldown <= 0)
  {
    invis_cooldown = 0;
    is_invis       = true;
    this->opacity(0.1F);
    weapon.opacity(0.1F);
    invis_timer = 0;
  }

  if(heal_button && heal_cooldown <= 0 && health < 100)
  {
    heal_cooldown = 0;
    healing = true;
    health += heal_amount;

    if(health > max_health)
    {
      health = 100;
    }
  }

  if(dash_button && dash_cooldown <= 0)
  {
    dash_timer = 0;
    dash_cooldown = 0;
    dashing = true;
    move_speed = 500;
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
  invisibility(dt);
  heal(dt);
  dash(dt);

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
bool Player::circleCollision(ASGE::Point2D position)
{
  auto diff = ASGE::Point2D(position.x - centre().x, position.y - centre().y);
  return (std::hypot(diff.x, diff.y) < 16);
}
void Player::invisibility(float dt)
{
  invis_cooldown -= dt;

  if(invis_cooldown <= 0.05 && invis_cooldown >= 0)
  {
    invis_recharged.play();
  }

  if (is_invis)
  {
    invis_timer += dt;

    if (invis_timer >= 5 || weapon.hasFired() || has_been_hit)
    {
      invis_timer    = 0;
      invis_cooldown = 15;
      is_invis       = false;
      this->opacity(1.0F);
      weapon.opacity(1.0F);
    }
  }
}
void Player::heal(float dt)
{
  heal_cooldown -= dt;

  if(heal_cooldown <= 0.05 && heal_cooldown >= 0)
  {
    invis_recharged.play();
  }

  if(healing)
  {
    heal_cooldown = 15;
    healing = false;
  }
}

void Player::dash(float dt)
{
  dash_cooldown -= dt;

  if(dash_cooldown <= 0.05 && dash_cooldown >= 0)
  {
    invis_recharged.play();
  }

  if (dashing)
  {
    dash_timer += dt;

    if (dash_timer >= 0.1 || weapon.hasFired() || has_been_hit)
    {
      dash_timer    = 0;
      dash_cooldown = 15;
      dashing       = false;
      move_speed    = 100;
    }
  }
}

