//
// Created by hewis on 12/05/2021.
//

#ifndef ASGEMOVIEGAME_KILLFEED_H
#define ASGEMOVIEGAME_KILLFEED_H

#include "ASGEGameLib/GameObjects/Sprites/Text.h"
#include <ASGEGameLib/GameObjects/Player/Player.hpp>
class KillFeedElement : public GameObject
{
 public:
  KillFeedElement(
    ASGE::Renderer* renderer, Player& p1, Player& p2, ASGE::Point2D _position,
    ASGE::Colour _colour);
  KillFeedElement(ASGE::Renderer* renderer, const std::string& message, ASGE::Point2D _position);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;
  void translate(ASGE::Point2D _translation);
  float timer = 5;
  Text name1;
  Text name2;
  Sprite weapon;
};
class KillFeed : public GameObject
{
 public:
  KillFeed(ASGE::Renderer* renderer, Player& _player, ASGE::Point2D _position);
  void addMessage(Player& p1, Player& p2);
  void addMessage(const std::string& message);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  ASGE::Renderer* m_renderer;
  Player& player;
  ASGE::Point2D position;
  std::vector<KillFeedElement> messages;
};

#endif // ASGEMOVIEGAME_KILLFEED_H
