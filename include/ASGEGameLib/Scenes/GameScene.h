//
// Created by hewis on 11/04/2021.
//

#ifndef ASGEMOVIEGAME_GAMESCENE_H
#define ASGEMOVIEGAME_GAMESCENE_H
#include "Scene.h"
class GameScene : public Scene
{
 public:
  GameScene(ASGE::Renderer* renderer, std::function<void(Scene::Scenes)> _scene_callback);
};

#endif // ASGEMOVIEGAME_GAMESCENE_H
