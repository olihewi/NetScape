//
// Created by hewis on 11/04/2021.
//

#ifndef ASGEMOVIEGAME_TITLESCENE_H
#define ASGEMOVIEGAME_TITLESCENE_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/UI/Cursor.h>
#include <ASGEGameLib/GameObjects/UI/UIButton.h>
#include <ASGEGameLib/Utilities/Sound.h>
class TitleScene : public Scene
{
 public:
  TitleScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);

  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  void selectButton(size_t _index);
  std::array<UIButton, 5> scene_change_buttons;
  Cursor cursor;
  size_t button_selection = 0;
  Sound test_clip;
};

#endif // ASGEMOVIEGAME_TITLESCENE_H
