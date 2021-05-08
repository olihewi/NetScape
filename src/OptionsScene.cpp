//
// Created by hewis on 16/04/2021.
//

#include "ASGEGameLib/Scenes/OptionsScene.h"

#include "ASGEGameLib/Utilities/FontManager.h"
#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
#include <utility>
OptionsScene::OptionsScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  instruction_text(
    renderer, "Press Any Button on the controller you would like to re-map.",
    ASGE::Point2D(400, 400), FONTS::ROBOTO),
  cursor(renderer, true),
  scene_change_buttons(std::array<UIButton, 1>{ UIButton(
    renderer, "data/images/ui/buttons/neon/pink.png", "Return to menu", FONTS::ROBOTO,
    [this]() { setScene(Scenes::TITLE); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
    ASGE::Point2D(1920 / 2.F - 375, 300), ASGE::Point2D(750, 125)) })
{
  instruction_text.centrePos(ASGE::Point2D(1920 / 2.F, 1080 / 2.F));
  std::unique_ptr<AnimatedSprite> background = std::make_unique<AnimatedSprite>(
    renderer, "data/images/animations/background.png", 20, ASGE::Point2D(0, -500));
  background->dimensions(ASGE::Point2D(1920, 1920));
  background->zOrder(-1);
  addObject(std::move(background));
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
        axis_rebind[current_input_rebind - 14] = static_cast<size_t>(this_axis);
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
  cursor.update(input, dt);
  for (auto& button : scene_change_buttons)
  {
    button.update(input, dt);
  }
}
void OptionsScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);
  instruction_text.render(renderer);
  cursor.render(renderer);
  for (auto& button : scene_change_buttons)
  {
    button.render(renderer);
  }
}
