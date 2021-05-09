//
// Created by Andrei on 29/04/2021.
//

#include "../include/ASGEGameLib/Scenes/CreditsScene.h"
#include <GameObjects/Sprites/AnimatedSprite.h>
#include <GameObjects/UI/ControllerDisplay.h>
#include <Utilities/FontManager.h>

CreditsScene::CreditsScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  scene_change_buttons(std::array<UIButton, 1>{ UIButton(
    renderer, "data/images/ui/buttons/neon/pink.png", "Press B to return to menu", FONTS::ROBOTO,
    [this]() { setScene(Scenes::TITLE); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
    ASGE::Point2D(
      static_cast<float>(ASGE::SETTINGS.window_width) / 2 - 375,
      static_cast<float>(ASGE::SETTINGS.window_height) * 0.75F),
    ASGE::Point2D(750, 125)) }),
  cursor(renderer)
{
  auto window = ASGE::Point2D(
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));
  std::unique_ptr<Text> game_title =
    std::make_unique<Text>(renderer, "NetScape", ASGE::Point2D(), FONTS::ROBOTO);
  std::unique_ptr<Text> credits_title =
    std::make_unique<Text>(renderer, "CREDITS", ASGE::Point2D(), FONTS::ROBOTO);
  std::unique_ptr<Text> credits_text = std::make_unique<Text>(
    renderer,
    "Game Developed by\n Oliver Hewison, Brad King,\n Matthew Bones, Andrei Barlea",
    ASGE::Point2D(),
    FONTS::ROBOTO);
  game_title->centrePos(ASGE::Point2D(window.x / 2.F, 150));
  credits_title->centrePos(ASGE::Point2D(window.x / 2.F, 350));
  credits_text->centrePos(ASGE::Point2D(window.x / 2.F, 550));
  addObject(std::move(game_title));
  addObject(std::move(credits_title));
  addObject(std::move(credits_text));
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
void CreditsScene::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);
  cursor.update(input, dt);
  if (input.getControllerButtonDown(0, CONTROLLER::BUTTONS::B))
  {
    setScene(Scenes::TITLE);
    return;
  }
  for (auto& button : scene_change_buttons)
  {
    button.update(input, dt);
  }
}
void CreditsScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);
  cursor.render(renderer);
  for (auto& button : scene_change_buttons)
  {
    button.render(renderer);
  }
}
