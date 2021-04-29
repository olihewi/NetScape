//
// Created by Bread on 08/04/2021.
//

#ifndef ASGEMOVIEGAME_PLAYER_HPP
#define ASGEMOVIEGAME_PLAYER_HPP

#include "ASGEGameLib/GameObjects/Player/Weapons/Weapon.h"
#include "ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h"
#include "ASGEGameLib/Utilities/InputTracker.h"
#include "ASGEGameLib/Utilities/LineTrace.h"
#include "ASGEGameLib/Utilities/Sound.h"

class Player : public AnimatedSprite
{
 public:
  Player(
    ASGE::Renderer* renderer, ASGE::Point2D _position, size_t control_id,
    SoLoud::Soloud* audio_engine);

  void render(ASGE::Renderer* renderer) override;

  void input(InputTracker& input, float dt);
  void position(ASGE::Point2D _position) override;
  void translate(ASGE::Point2D _translation) override;

  void fire();

  void takeDamage(float damage);



  float move_speed = 100.0F;
  float health     = 100.0F;

 private:
  size_t controller_id;
  Sound player_walk;
  Weapon weapon;

 public:
  const Weapon& getWeapon() const;
};

#endif // ASGEMOVIEGAME_PLAYER_HPP
