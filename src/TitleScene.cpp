//
// Created by hewis on 11/04/2021.
//

#include "Scenes/TitleScene.h"
#include "Utilities/FontManager.h"
#include <cmath>
#include <iostream>
TitleScene::TitleScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  scene_change_buttons(std::array<UIButton, 5>{
    UIButton(
      renderer, "data/images/ui/buttons/neon/pink.png", "Play", FONTS::ROBOTO,
      [this]() { setScene(Scenes::GAME); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(1920 / 2.F - 375, 400), ASGE::Point2D(750, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/purple.png", "Level Editor", FONTS::ROBOTO,
      [this]() { setScene(Scenes::LEVEL_EDITOR); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(1920 / 2.F - 375, 525), ASGE::Point2D(750, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/blue.png", "Options", FONTS::ROBOTO, []() {},
      std::array<float, 6>{ 11, 11, 114, 50, 11, 11 }, ASGE::Point2D(1920 / 2.F - 375, 650),
      ASGE::Point2D(375, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/green.png", "Credits", FONTS::ROBOTO, []() {},
      std::array<float, 6>{ 11, 11, 114, 50, 11, 11 }, ASGE::Point2D(1920 / 2.F, 650),
      ASGE::Point2D(375, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/yellow.png", "Quit Game", FONTS::ROBOTO,
      [this]() { setScene(Scenes::QUIT_GAME); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(1920 / 2.F - 375, 775), ASGE::Point2D(750, 125)) }),
  cursor(renderer), test_clip(audio_engine.get(), "data/audio/8ball.wav")
{
  std::unique_ptr<Text> game_title =
    std::make_unique<Text>(renderer, "NetScape", ASGE::Point2D(), FONTS::ROBOTO);
  game_title->centrePos(ASGE::Point2D(1920 / 2.F, 350));
  addObject(std::move(game_title));
  selectButton(button_selection);
  test_clip.getSound().setLooping(true);
  test_clip.play();
}
void TitleScene::clickInput(const ASGE::ClickEvent* click)
{
  Scene::clickInput(click);
  for (auto& button : scene_change_buttons)
  {
    bool should_return = button.isInside(
      ASGE::Point2D(static_cast<float>(click->xpos), static_cast<float>(click->ypos)));
    button.clickInput(click);
    if (should_return)
    {
      return;
    }
  }
}
void TitleScene::mouseInput(const ASGE::MoveEvent* mouse)
{
  Scene::mouseInput(mouse);
  cursor.setCursor(Cursor::POINTER);
  size_t index = 0;
  for (auto& button : scene_change_buttons)
  {
    button.mouseInput(mouse);
    if (button.isInside(
          ASGE::Point2D(static_cast<float>(mouse->xpos), static_cast<float>(mouse->ypos))))
    {
      cursor.setCursor(Cursor::SELECT);
      button_selection = index;
    }
    index++;
  }
  cursor.mouseInput(mouse);
}
void TitleScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);
  for (auto& button : scene_change_buttons)
  {
    button.render(renderer);
  }
  cursor.render(renderer);
}
void TitleScene::controllerInput(ControllerTracker& controllers, float /*dt*/)
{
  if (controllers.getButtonDown(0, CONTROLLER::BUTTONS::A))
  {
    for (auto& button : scene_change_buttons)
    {
      if (button.press())
      {
        return;
      }
    }
  }
  else if (
    (controllers.getAxisUp(0, CONTROLLER::AXIS::LEFT_STICK_Y) ||
     controllers.getButtonDown(0, CONTROLLER::BUTTONS::DPAD_DOWN)) &&
    button_selection < scene_change_buttons.size() - 1)
  {
    button_selection += (button_selection == 2 ? 2 : 1);
    selectButton(button_selection);
    cursor.visibility(false);
  }
  else if (
    (controllers.getAxisDown(0, CONTROLLER::AXIS::LEFT_STICK_Y) ||
     controllers.getButtonDown(0, CONTROLLER::BUTTONS::DPAD_UP)) &&
    button_selection > 0)
  {
    button_selection -= (button_selection >= 3 ? 2 : 1);
    selectButton(button_selection);
    cursor.visibility(false);
  }
  else if (
    (controllers.getAxisDown(0, CONTROLLER::AXIS::LEFT_STICK_X) ||
     controllers.getButtonDown(0, CONTROLLER::BUTTONS::DPAD_LEFT)) &&
    button_selection == 3)
  {
    button_selection--;
    selectButton(button_selection);
    cursor.visibility(false);
  }
  else if (
    (controllers.getAxisUp(0, CONTROLLER::AXIS::LEFT_STICK_X) ||
     controllers.getButtonDown(0, CONTROLLER::BUTTONS::DPAD_RIGHT)) &&
    button_selection == 2)
  {
    button_selection++;
    selectButton(button_selection);
    cursor.visibility(false);
  }
}
void TitleScene::selectButton(size_t _index)
{
  for (auto& button : scene_change_buttons)
  {
    button.select(false);
  }
  scene_change_buttons[_index].select(true);
}
