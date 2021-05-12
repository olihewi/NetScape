//
// Created by Bread on 12/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERABILITIES_HPP
#define ASGEMOVIEGAME_PLAYERABILITIES_HPP

#include <ASGEGameLib/GameObjects/GameObject.h>
#include <ASGEGameLib/GameObjects/Player/Player.hpp>
#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>

class PlayerAbilities : public GameObject
{
 public:
  PlayerAbilities(ASGE::Renderer* renderer, Player& _player, float x, float y);

  void update(InputTracker& input, float dt) override;

  void render(ASGE::Renderer* renderer) override;

 private:
  Player& player;
  ASGE::Point2D position;

  std::array<Sprite, 3> ability_icons;
};


#endif // ASGEMOVIEGAME_PLAYERABILITIES_HPP
