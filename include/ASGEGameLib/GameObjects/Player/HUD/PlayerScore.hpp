//
// Created by Work on 12/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERSCORE_HPP
#define ASGEMOVIEGAME_PLAYERSCORE_HPP

#include <ASGEGameLib/GameObjects/Player/Player.hpp>
#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>

class PlayerScore : public GameObject
{
 public:
  PlayerScore(ASGE::Renderer* renderer, Player& _player, float x, float y);

  void update(InputTracker& input, float dt) override;

  void render(ASGE::Renderer* renderer) override;

 private:
  bool display_score_sheet = false;
  ASGE::Point2D position;
  Player& player;
  Sprite score_card;
  std::array<Text, 6> score_text;

  int current_favourite_weapon_index = 0;
  std::string favourite_weapon;
};

#endif // ASGEMOVIEGAME_PLAYERSCORE_HPP
