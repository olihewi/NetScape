//
// Created by hewis on 11/04/2021.
//

#include "Scenes/TitleScene.h"
#include "Utilities/FontManager.h"
#include <ASGEGameLib/GameObjects/Sprites/AnimatedSprite.h>
#include <ASGEGameLib/GameObjects/UI/ControllerDisplay.h>
#include <cmath>
#include <iostream>
TitleScene::TitleScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  scene_change_buttons(std::array<UIButton, 5>{
    UIButton(
      renderer, "data/images/ui/buttons/neon/pink.png", "Play", FONTS::ROBOTO,
      [this]() { setScene(Scenes::GAME); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(
        static_cast<float>(ASGE::SETTINGS.window_width) / 2 - 375,
        static_cast<float>(ASGE::SETTINGS.window_height) / 2 - 125),
      ASGE::Point2D(750, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/purple.png", "Level Editor", FONTS::ROBOTO,
      [this]() { setScene(Scenes::LEVEL_EDITOR); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(
        static_cast<float>(ASGE::SETTINGS.window_width) / 2 - 375,
        static_cast<float>(ASGE::SETTINGS.window_height) / 2),
      ASGE::Point2D(750, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/blue.png", "Options", FONTS::ROBOTO,
      [this]() { setScene(Scenes::OPTIONS); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(
        static_cast<float>(ASGE::SETTINGS.window_width) / 2 - 375,
        static_cast<float>(ASGE::SETTINGS.window_height) / 2 + 125),
      ASGE::Point2D(375, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/green.png", "Credits", FONTS::ROBOTO,
      [this]() { setScene(Scenes::CREDITS); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(
        static_cast<float>(ASGE::SETTINGS.window_width) / 2,
        static_cast<float>(ASGE::SETTINGS.window_height) / 2 + 125),
      ASGE::Point2D(375, 125)),
    UIButton(
      renderer, "data/images/ui/buttons/neon/yellow.png", "Quit Game", FONTS::ROBOTO,
      [this]() { setScene(Scenes::QUIT_GAME); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(
        static_cast<float>(ASGE::SETTINGS.window_width) / 2 - 375,
        static_cast<float>(ASGE::SETTINGS.window_height) / 2 + 250),
      ASGE::Point2D(750, 125)) }),
  cursor(renderer), test_clip(audio_engine.get(), "data/audio/8ball.wav")
{
  auto window = ASGE::Point2D(
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));
  std::unique_ptr<Text> game_title =
    std::make_unique<Text>(renderer, "NetScape", ASGE::Point2D(), FONTS::BARCODE);
  game_title->centrePos(ASGE::Point2D(window.x / 2, window.y / 2 - 150));
  addObject(std::move(game_title));
  selectButton(button_selection);
  test_clip.getSound().setLooping(true);
  test_clip.play();
  std::unique_ptr<AnimatedSprite> background = std::make_unique<AnimatedSprite>(
    renderer, "data/images/animations/background.png", 20, ASGE::Point2D(0, -window.x / 4));
  background->dimensions(ASGE::Point2D(window.x, window.x));
  background->zOrder(-1);
  addObject(std::move(background));
  addObject(std::make_unique<ControllerDisplay>(
    renderer, 0, ASGE::Point2D(100, 100), ASGE::Point2D(window.x / 5, window.x / 7.5F)));
  addObject(std::make_unique<ControllerDisplay>(
    renderer,
    1,
    ASGE::Point2D(window.x - window.x / 5 - 100, 100),
    ASGE::Point2D(window.x / 5, window.x / 7.5F)));
  addObject(std::make_unique<ControllerDisplay>(
    renderer,
    2,
    ASGE::Point2D(100, window.y - window.x / 7.5F - 100),
    ASGE::Point2D(window.x / 5, window.x / 7.5F)));
  addObject(std::make_unique<ControllerDisplay>(
    renderer,
    3,
    ASGE::Point2D(window.x - window.x / 5 - 100, window.y - window.x / 7.5F - 100),
    ASGE::Point2D(window.x / 5, window.x / 7.5F)));
}
void TitleScene::controllerInputs(InputTracker& input)
{
  if (
    (input.getControllerAxisUp(0, CONTROLLER::AXIS::LEFT_STICK_Y) ||
     input.getControllerButtonDown(0, CONTROLLER::BUTTONS::DPAD_DOWN) ||
     input.getKeyDown(ASGE::KEYS::KEY_S)) &&
    button_selection < scene_change_buttons.size() - 1)
  {
    button_selection += (button_selection == 2 ? 2 : 1);
    selectButton(button_selection);
    cursor.visibility(false);
  }
  if (
    (input.getControllerAxisDown(0, CONTROLLER::AXIS::LEFT_STICK_Y) ||
     input.getControllerButtonDown(0, CONTROLLER::BUTTONS::DPAD_UP) ||
     input.getKeyDown(ASGE::KEYS::KEY_W)) &&
    button_selection > 0)
  {
    button_selection -= (button_selection >= 3 ? 2 : 1);
    selectButton(button_selection);
    cursor.visibility(false);
  }
  if (
    (input.getControllerAxisDown(0, CONTROLLER::AXIS::LEFT_STICK_X) ||
     input.getControllerButtonDown(0, CONTROLLER::BUTTONS::DPAD_LEFT) ||
     input.getKeyDown(ASGE::KEYS::KEY_A)) &&
    button_selection == 3)
  {
    button_selection--;
    selectButton(button_selection);
    cursor.visibility(false);
  }
  if (
    (input.getControllerAxisUp(0, CONTROLLER::AXIS::LEFT_STICK_X) ||
     input.getControllerButtonDown(0, CONTROLLER::BUTTONS::DPAD_RIGHT) ||
     input.getKeyDown(ASGE::KEYS::KEY_D)) &&
    button_selection == 2)
  {
    button_selection++;
    selectButton(button_selection);
    cursor.visibility(false);
  }
}
void TitleScene::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);
  cursor.setCursor(Cursor::POINTER);
  cursor.update(input, dt);
  controllerInputs(input);
  size_t index = 0;
  for (auto& button : scene_change_buttons)
  {
    if (button.isInside(input.getMousePos()))
    {
      cursor.setCursor(Cursor::SELECT);
      if (input.hasHadMouseInput())
      {
        button_selection = index;
      }
    }
    bool should_return =
      (input.getMouseButton(MOUSE::LEFT_CLICK) && button.isInside(input.getMousePos())) ||
      (input.getControllerButton(0, CONTROLLER::BUTTONS::A) && button_selection == index);
    button.update(input, dt);
    if (should_return)
    {
      return;
    }
    index++;
  }
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
void TitleScene::selectButton(size_t _index)
{
  for (auto& button : scene_change_buttons)
  {
    button.select(false);
  }
  scene_change_buttons[_index].select(true);
}
