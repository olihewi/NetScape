//
// Created by Bread on 08/04/2021.
//

#ifndef ASGEMOVIEGAME_PLAYER_HPP
#define ASGEMOVIEGAME_PLAYER_HPP

#include "ASGEGameLib/GameObjects/GameObject.h"
#include "ASGEGameLib/GameObjects/Sprites/Sprite.h"

class Player : public GameObject
{
 public:
  //  Player(ASGE::Renderer);

  void movement();

  float move_speed = 5.0F;
};

#endif // ASGEMOVIEGAME_PLAYER_HPP
