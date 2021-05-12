//
// Created by hewis on 08/05/2021.
//

#ifndef ASGEMOVIEGAME_PLAYERHUD_H
#define ASGEMOVIEGAME_PLAYERHUD_H

#include <ASGEGameLib/GameObjects/Player/HUD/KillFeed.h>
#include <ASGEGameLib/GameObjects/Player/Player.hpp>
class PlayerHUD : public GameObject
{
 public:
  PlayerHUD(ASGE::Renderer* renderer, Player& _player);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;
  void addObject(std::unique_ptr<GameObject> _object);
  void cameraShake(ASGE::Point2D _shake);
  [[nodiscard]] ASGE::Point2D getCameraShake();
  void addKillFeed(Player& p1, Player& p2);

  [[nodiscard]] float getFocus() const;

 private:
  Player& player;
  std::vector<std::unique_ptr<GameObject>> objects;
  float lerped_focus         = 0;
  ASGE::Point2D camera_shake = ASGE::Point2D();
  KillFeed kill_feed;
};

#endif // ASGEMOVIEGAME_PLAYERHUD_H
