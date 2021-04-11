//
// Created by hewis on 11/04/2021.
//

#include "Scenes/TitleScene.h"
#include "Utilities/FontManager.h"
TitleScene::TitleScene(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)),
  scene_change_buttons(std::array<UIButton, 2>{
    UIButton(
      renderer, "data/images/ui/buttons/neon_pink.png", "Level Editor", FONTS::ROBOTO,
      [this]() { setScene(Scenes::LEVEL_EDITOR); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(1920 / 2.F - 250, 650), ASGE::Point2D(500, 150)),
    UIButton(
      renderer, "data/images/ui/buttons/neon_pink.png", "Quit Game", FONTS::ROBOTO,
      [this]() { setScene(Scenes::QUIT_GAME); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
      ASGE::Point2D(1920 / 2.F - 250, 800), ASGE::Point2D(500, 150)) })
{
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
  for (auto& button : scene_change_buttons)
  {
    button.mouseInput(mouse);
  }
}
void TitleScene::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);
  for (auto& button : scene_change_buttons)
  {
    button.render(renderer);
  }
}
