//
// Created by hewis on 11/04/2021.
//

#ifndef ASGEMOVIEGAME_TITLESCENE_H
#define ASGEMOVIEGAME_TITLESCENE_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/UI/UIButton.h>
class TitleScene : public Scene
{
 public:
  TitleScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);

  void clickInput(const ASGE::ClickEvent* click) override;
  void mouseInput(const ASGE::MoveEvent* mouse) override;
  void render(ASGE::Renderer* renderer) override;
  void controllerInput(std::array<ASGE::GamePadData, 4> controllers) override;

 private:
  std::array<UIButton, 4> scene_change_buttons;
};

#endif // ASGEMOVIEGAME_TITLESCENE_H
