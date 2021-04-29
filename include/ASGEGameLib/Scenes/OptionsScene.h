//
// Created by hewis on 16/04/2021.
//

#ifndef ASGEMOVIEGAME_OPTIONSSCENE_H
#define ASGEMOVIEGAME_OPTIONSSCENE_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/UI/Cursor.h>
#include <ASGEGameLib/GameObjects/UI/UIButton.h>
class OptionsScene : public Scene
{
 public:
  OptionsScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  std::array<std::string, 20> instructions{ "Press A",
                                            "Press B",
                                            "Press X",
                                            "Press Y",
                                            "Press Left Shoulder",
                                            "Press Right Shoulder",
                                            "Press Back",
                                            "Press Start",
                                            "Press Left Stick",
                                            "Press Right Stick",
                                            "Press D-Pad Up",
                                            "Press D-Pad Right",
                                            "Press D-Pad Down",
                                            "Press D-Pad Left",
                                            "Move Left Stick Horizontally",
                                            "Move Left Stick Vertically",
                                            "Move Right Stick Horizontally",
                                            "Move Right Stick Vertically",
                                            "Pull Left Trigger",
                                            "Pull Right Trigger" };
  size_t current_input_rebind = 0;
  int this_controller         = -1;
  Text instruction_text;
  Cursor cursor;
  std::array<UIButton, 1> scene_change_buttons;
  std::unordered_map<size_t, size_t> button_rebind;
  std::unordered_map<size_t, size_t> axis_rebind;
};

#endif // ASGEMOVIEGAME_OPTIONSSCENE_H
