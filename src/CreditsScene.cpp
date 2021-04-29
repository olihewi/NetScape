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
    ASGE::Point2D(1920 / 2.F - 375, 800), ASGE::Point2D(750, 125)) }),
  cursor(renderer)
{
  std::unique_ptr<Text> game_title =
    std::make_unique<Text>(renderer, "NetScape", ASGE::Point2D(), FONTS::ROBOTO);
  std::unique_ptr<Text> credits_title =
    std::make_unique<Text>(renderer, "CREDITS", ASGE::Point2D(), FONTS::ROBOTO);
  std::unique_ptr<Text> credits_text = std::make_unique<Text>(
    renderer,
    "Game Developed by\n Oliver Hewison, Brad King,\n Matthew Bones, Andrei Barlea",
    ASGE::Point2D(),
    FONTS::ROBOTO);
  game_title->centrePos(ASGE::Point2D(1920 / 2.F, 150));
  credits_title->centrePos(ASGE::Point2D(1920 / 2.F, 350));
  credits_text->centrePos(ASGE::Point2D(1920 / 2.F, 550));
  addObject(std::move(game_title));
  addObject(std::move(credits_title));
  addObject(std::move(credits_text));
  std::unique_ptr<AnimatedSprite> background = std::make_unique<AnimatedSprite>(
    renderer, "data/images/animations/background.png", 20, ASGE::Point2D(0, -500));
  background->dimensions(ASGE::Point2D(1920, 1920));
  background->zOrder(-1);
  addObject(std::move(background));
  addObject(std::make_unique<ControllerDisplay>(
    renderer, 0, ASGE::Point2D(100, 100), ASGE::Point2D(400, 280)));
  addObject(std::make_unique<ControllerDisplay>(
    renderer, 1, ASGE::Point2D(1420, 100), ASGE::Point2D(400, 280)));
  addObject(std::make_unique<ControllerDisplay>(
    renderer, 2, ASGE::Point2D(100, 700), ASGE::Point2D(400, 280)));
  addObject(std::make_unique<ControllerDisplay>(
    renderer, 3, ASGE::Point2D(1420, 700), ASGE::Point2D(400, 280)));
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
