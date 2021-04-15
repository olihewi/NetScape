//
// Created by hewis on 11/04/2021.
//

#ifndef ASGEMOVIEGAME_GAMESCENE_H
#define ASGEMOVIEGAME_GAMESCENE_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/Player/Player.hpp>
#include <ASGEGameLib/GameObjects/UI/Cursor.h>
#include <ASGEGameLib/GameObjects/UI/UIButton.h>

class GameScene : public Scene
{
 public:
  GameScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);

  void render(ASGE::Renderer* renderer) override;
  void controllerInput(ControllerTracker& controllers, float dt) override;

 private:
};

#endif // ASGEMOVIEGAME_GAMESCENE_H
