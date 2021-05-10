//
// Created by Work on 08/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERAMMO_HPP
#define ASGEMOVIEGAME_PLAYERAMMO_HPP

#include <ASGEGameLib/GameObjects/Player/Player.hpp>
#include <ASGEGameLib/GameObjects/Player/Weapons/Weapon.h>
#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>

class PlayerAmmo : public GameObject
{
 public:
  PlayerAmmo(
    ASGE::Renderer* renderer, Weapon& _weapon, Player& _player, float x, float y);

  void update(InputTracker& input, float dt) override;

  void render(ASGE::Renderer* renderer) override;

 private:
  Weapon& weapon;
  Player& player;
  std::array<Sprite, 10> bullet;
  // Sprite background;
  float posX, posY;
  int AmmoReserve;
  Text AmmoReserveDisplay;
};

#endif // ASGEMOVIEGAME_PLAYERAMMO_HPP
