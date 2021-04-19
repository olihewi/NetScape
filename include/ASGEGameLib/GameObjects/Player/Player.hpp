//
// Created by Bread on 08/04/2021.
//

#ifndef ASGEMOVIEGAME_PLAYER_HPP
#define ASGEMOVIEGAME_PLAYER_HPP

#include "ASGEGameLib/GameObjects/GameObject.h"
#include "ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h"
#include "ASGEGameLib/GameObjects/Sprites/Sprite.h"
#include "ASGEGameLib/Utilities/InputTracker.h"

class Player : public AnimatedSprite
{
 public:
  Player(
    ASGE::Renderer* renderer, const std::string& file_path, ASGE::Point2D _position,
    ASGE::Point2D _dimensions, size_t playback_speed, short z_order = 1, int control_id = -1);

  void render(ASGE::Renderer* renderer) override;

  void input(InputTracker& input, float dt);

  float move_speed = 50.0f;
  float health     = 100;

 private:
  int controller_id;
};

#endif // ASGEMOVIEGAME_PLAYER_HPP
