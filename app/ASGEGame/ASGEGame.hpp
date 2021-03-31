//
// Created by huxy on 23/02/2020.
//

#pragma once

#include <ASGEGameLib/GComponent.hpp>
#include <Engine/OGLGame.h>
#include <vector>

class ASGEGame : public ASGE::OGLGame
{
 public:
  explicit ASGEGame(const ASGE::GameSettings& settings);
  ~ASGEGame() override;

  ASGEGame(const ASGEGame&) = delete;
  ASGEGame& operator=(const ASGEGame&) = delete;

  void keyHandler(ASGE::SharedEventData data);
  void update(const ASGE::GameTime& us) override;
  void render() override;
  void fixedUpdate(const ASGE::GameTime& us) override;

 private:
  std::vector<std::unique_ptr<GameComponent>> game_components;
  int key_callback_id = -1; /**< Key Input Callback ID. */
};
