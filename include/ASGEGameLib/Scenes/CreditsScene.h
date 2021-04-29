//
// Created by Andrei on 29/04/2021.
//

#ifndef ASGEMOVIEGAME_CREDITSSCENE_H
#define ASGEMOVIEGAME_CREDITSSCENE_H
#include "Scene.h"
#include <ASGEGameLib/GameObjects/UI/Cursor.h>
#include <ASGEGameLib/GameObjects/UI/UIButton.h>
class CreditsScene : public Scene
{
 public:
  CreditsScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);

  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  std::array<UIButton, 1> scene_change_buttons;
  Cursor cursor;
};

#endif // ASGEMOVIEGAME_CREDITSSCENE_H
