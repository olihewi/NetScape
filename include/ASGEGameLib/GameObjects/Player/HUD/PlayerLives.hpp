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
  Sprite lives;
  ASGE::Point2D position;
  Sprite health_bd;
  Sprite health_bg;
  Sprite health_bar;

  Text player_name;

  void playerRespawn();
};

#endif // ASGEMOVIEGAME_PLAYERLIVES_HPP
