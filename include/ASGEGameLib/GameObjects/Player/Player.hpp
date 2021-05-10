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

  float move_speed = 100.0F;
  bool is_dead     = false;

  bool has_been_hit        = false;
  float has_been_hit_timer = 0;

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
};

#endif // ASGEMOVIEGAME_PLAYER_HPP
