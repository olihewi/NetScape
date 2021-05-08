//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_TESTSCENE_H
#define ASGEMOVIEGAME_TESTSCENE_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
class TestScene : public Scene
{
 public:
  TestScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);

  void update(InputTracker &input, float dt) override;

  void render(ASGE::Renderer *renderer) override;

 private:
  AnimatedSprite crow_sprite;


};

#endif // ASGEMOVIEGAME_TESTSCENE_H
