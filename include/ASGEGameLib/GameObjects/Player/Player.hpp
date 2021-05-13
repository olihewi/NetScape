//
// Created by Bread on 08/04/2021.
//

#ifndef ASGEMOVIEGAME_PLAYER_HPP
#define ASGEMOVIEGAME_PLAYER_HPP

#include "ASGEGameLib/GameObjects/GameObject.h"
#include "ASGEGameLib/GameObjects/Player/Weapons/Weapon.h"
#include "ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h"
#include "ASGEGameLib/GameObjects/Sprites/Text.h"
#include "ASGEGameLib/Utilities/InputTracker.h"
#include "ASGEGameLib/Utilities/Sound.h"
struct Score
{
 public:
  int kills      = 0;
  int deaths     = 0;
  float hit      = 0;
  float miss     = 0;
  int kill_spree = 0;
  bool game_end       = false;

  std::array<int, 4> nemesis_points{};
  std::unordered_map<std::string, int> favourite_gun{};
  // Pistol, Shotgun, Uzi, Sniper
};

class Player : public AnimatedSprite
{
 public:
  Player(
    ASGE::Renderer* renderer, ASGE::Point2D _position, size_t control_id,
    SoLoud::Soloud* audio_engine);

  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

  void input(InputTracker& input, float dt);
  void position(ASGE::Point2D _position) override;
  void translate(ASGE::Point2D _translation) override;

  void takeDamage(float damage);

  [[nodiscard]] size_t getID() const;

  Weapon& getWeapon();
  [[nodiscard]] float getMaxHealth() const;
  // void setMaxHealth(float _maxhealth);

  [[nodiscard]] float getHealth() const;
  void setHealth(float _health);

  [[nodiscard]] int getMaxLives() const;
  [[nodiscard]] int getLives() const;
  void setLives(int _lives);

  [[nodiscard]] ASGE::Point2D getSpawnPoint();
  void setSpawnPoint(ASGE::Point2D _spawn_point);

  // Abilities
  void invisibility(float dt);
  float invis_cooldown = 0;
  float invis_timer    = 0;
  bool is_invis        = false;

  void heal(float dt);
  bool healing        = false;
  float heal_cooldown = 0;
  float heal_amount   = 50;

  void dash(float dt);
  bool dashing        = false;
  float dash_cooldown = 0;
  float dash_timer    = 0;

  float move_speed = 100.0F;
  bool is_dead     = false;

  bool has_been_hit        = false;
  float has_been_hit_timer = 0;

  Score& getScore();

  [[nodiscard]] bool circleCollision(ASGE::Point2D position);

 private:
  float max_health = 100.0F;
  float health     = max_health;
  size_t controller_id;
  Weapon weapon;
  Sound player_walk;
  int max_lives = 10;
  int lives;
  Sound player_damaged;
  float playerR = 1, playerG = 1, playerB = 1;
  float colour_gain = 1.5F;
  ASGE::Point2D spawn_point;
  Score score;
  Sound player_killed;
  Sound invis_recharged;
};

/// STRUCTS

#endif // ASGEMOVIEGAME_PLAYER_HPP
