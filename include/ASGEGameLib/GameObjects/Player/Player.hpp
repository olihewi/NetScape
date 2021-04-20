//
// Created by Bread on 08/04/2021.
//

#ifndef ASGEMOVIEGAME_PLAYER_HPP
#define ASGEMOVIEGAME_PLAYER_HPP

#include "ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h"
#include "ASGEGameLib/Utilities/InputTracker.h"
#include "ASGEGameLib/Utilities/Sound.h"

class Player : public AnimatedSprite
{
 public:
  Player(
    ASGE::Renderer* renderer, const std::string& file_path, ASGE::Point2D _position,
    ASGE::Point2D _dimensions, float playback_speed, short z_order, size_t control_id);

  void render(ASGE::Renderer* renderer) override;

  void input(InputTracker& input, float dt);

  void fire();

  float move_speed = 50.0F;
  float health     = 100.0F;

 private:
  size_t controller_id;
};

#endif // ASGEMOVIEGAME_PLAYER_HPP
