//
// Created by Work on 07/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERHEALTH_HPP
#define ASGEMOVIEGAME_PLAYERHEALTH_HPP

#include <ASGEGameLib/GameObjects/Player/Player.hpp>
#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>

class PlayerHealth : public Sprite
{
 public:
  PlayerHealth(ASGE::Renderer* renderer, Player& _player);

  void update(InputTracker& input, float dt) override;

  void render(ASGE::Renderer* renderer) override;

 private:
  Player& player;
  Sprite background;

  //
};

#endif // ASGEMOVIEGAME_PLAYERHEALTH_HPP
