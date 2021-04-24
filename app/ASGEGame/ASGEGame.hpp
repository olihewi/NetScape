//
// Created by huxy on 23/02/2020.
//

#pragma once

#include <ASGEGameLib/Scenes/Scene.h>
#include <Engine/OGLGame.hpp>
#include <vector>

class ASGEGame : public ASGE::OGLGame
{
 public:
  explicit ASGEGame(const ASGE::GameSettings& settings);
  ~ASGEGame() override = default;

  ASGEGame(const ASGEGame&) = delete;
  ASGEGame& operator=(const ASGEGame&) = delete;

  void update(const ASGE::GameTime& us) override; // fixed update
  void render(const ASGE::GameTime& us) override; // render and regular update

  void setScene(Scene::Scenes _scene);

 private:
  std::unique_ptr<Scene> scene;
  InputTracker input_tracker;
};
