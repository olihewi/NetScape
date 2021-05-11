//
// Created by hewis on 11/04/2021.
//

#ifndef ASGEMOVIEGAME_GAMESCENE_H
#define ASGEMOVIEGAME_GAMESCENE_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/Player/HUD/PlayerHUD.h>
#include <ASGEGameLib/GameObjects/Player/Player.hpp>
#include <ASGEGameLib/GameObjects/Tilemap/TileMap.h>
#include <ASGEGameLib/GameObjects/UI/Cursor.h>
#include <ASGEGameLib/GameObjects/UI/UIButton.h>
#include <Engine/Camera.hpp>

class GameScene : public Scene
{
 public:
  GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);

  void render(ASGE::Renderer* renderer) override;
  void update(InputTracker& input, float dt) override;

 private:
  void playerMovement(InputTracker& input, float dt);
  void checkBullets();
  ASGE::Point2D playerVsTiles(InputTracker& input, float dt, Player& player);
  [[nodiscard]] bool playerCollidesWithTile(ASGE::Point2D player, ASGE::Point2D tile);
  void updateDrops(InputTracker& input);
  ASGE::Renderer* m_renderer;
  TileMap tile_map;
  std::array<Player, 4> players;
  Sprite window_divider;
  std::vector<std::pair<ASGE::Camera, PlayerHUD>> player_cameras;
  float round_timer = 120;
  Text round_time_text;

  // std::array<ASGE::Camera, 4> player_cameras;
};

#endif // ASGEMOVIEGAME_GAMESCENE_H
