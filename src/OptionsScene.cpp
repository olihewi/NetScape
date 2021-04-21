//
// Created by hewis on 16/04/2021.
//

#include "ASGEGameLib/Scenes/OptionsScene.h"

#include "ASGEGameLib/Utilities/FontManager.h"
#include <utility>
OptionsScene::OptionsScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  instruction_text(
    renderer, "Press Any Button on the controller you would like to re-map.",
    ASGE::Point2D(400, 400), FONTS::ROBOTO)
{
  instruction_text.centrePos(ASGE::Point2D(1920 / 2.F, 1080 / 2.F));
}
void OptionsScene::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);
  if (this_controller == -1)
  {
    this_controller = input.getLastController();
    if (this_controller != -1)
    {
      instruction_text.contents(instructions[current_input_rebind]);
      instruction_text.centrePos(ASGE::Point2D(1920 / 2.F, 1080 / 2.F));
    }
  }
  else
  {
    if (current_input_rebind < 14) /// Buttons
    {
      auto this_button = input.getLastControllerButton(static_cast<size_t>(this_controller));
      if (this_button != -1)
      {
        button_rebind[current_input_rebind] = static_cast<size_t>(this_button);
        current_input_rebind++;
      }
    }
    else /// Axis
    {
      auto this_axis = input.getLastControllerAxis(static_cast<size_t>(this_controller));
      if (this_axis != -1)
      {
        axis_rebind[static_cast<size_t>(current_input_rebind - 14)] = this_axis;
        current_input_rebind++;
        if (current_input_rebind == 20)
        {
          input.setControllerBinding(
            static_cast<size_t>(this_controller), button_rebind, axis_rebind);
          setScene(Scene::TITLE);
          return;
        }
      }
    }
    instruction_text.contents(instructions[current_input_rebind]);
    instruction_text.centrePos(ASGE::Point2D(1920 / 2.F, 1080 / 2.F));
  }
}
void OptionsScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);
  instruction_text.render(renderer);
}
