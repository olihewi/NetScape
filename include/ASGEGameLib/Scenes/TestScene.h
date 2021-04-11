//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_TESTSCENE_H
#define ASGEMOVIEGAME_TESTSCENE_H

#include "Scene.h"
class TestScene : public Scene
{
 public:
  TestScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);
};

#endif // ASGEMOVIEGAME_TESTSCENE_H
