//
// Created by Work on 10/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERLIVES_HPP
#define ASGEMOVIEGAME_PLAYERLIVES_HPP

#include <ASGEGameLib/GameObjects/Player/Player.hpp>
#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
class PlayerLives : public GameObject
{
 public:
  PlayerLives(ASGE::Renderer* renderer, Player& _player, float x, float y);

  void update(InputTracker& input, float dt) override;

  void render(ASGE::Renderer* renderer) override;
 private:
  Player& player;
  std::array<Sprite, 10> lives;
  float posX, posY;

  Text LivesReserveDisplay;
  Text LivesReserveDisplayX;

  void playerRespawn();


};

#endif // ASGEMOVIEGAME_PLAYERLIVES_HPP
