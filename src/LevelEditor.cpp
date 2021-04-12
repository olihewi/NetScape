//
// Created by hewis on 01/04/2021.
//

#include "Scenes/LevelEditor.h"

#include "Utilities/FontManager.h"
#include <utility>
LevelEditor::LevelEditor(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), tile_map(renderer, 1),
  tile_set(renderer, "data/images/tilesets/japanese_city.png"),
  scene_change_buttons(std::array<UIButton, 1>{ UIButton(
    renderer, "data/images/ui/buttons/neon/yellow.png", "Exit", FONTS::ROBOTO,
    [this]() { setScene(Scenes::TITLE); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
    ASGE::Point2D(1920 - 375, 0), ASGE::Point2D(375, 125)) }),
  cursor(renderer)
{
}
void LevelEditor::update(float dt)
{
  Scene::update(dt);
  tile_map.update(dt);
}
void LevelEditor::render(ASGE::Renderer* renderer)
{
  Scene::render(renderer);
  tile_set.render(renderer);
  tile_map.render(renderer);
  for (auto& button : scene_change_buttons)
  {
    button.render(renderer);
  }
  cursor.render(renderer);
}
void LevelEditor::keyInput(const ASGE::KeyEvent* key)
{
  Scene::keyInput(key);
}
void LevelEditor::clickInput(const ASGE::ClickEvent* click)
{
  tile_set.clickInput(click);
  mouse_pressed  = click->action != ASGE::KEYS::KEY_RELEASED;
  auto click_pos = ASGE::Point2D(static_cast<float>(click->xpos), static_cast<float>(click->ypos));
  if (click_pos.x >= 256 && click->action == ASGE::KEYS::KEY_PRESSED)
  {
    auto x_pos = static_cast<size_t>(click_pos.x) / 32;
    auto y_pos = static_cast<size_t>(click_pos.y) / 32;
    if (x_pos < 50 && y_pos < 50)
    {
      tile_map.setTile(
        0, x_pos + y_pos * 50, "data/images/tilesets/japanese_city.png", tile_set.getCurrentRect());
    }
  }
  for (auto& button : scene_change_buttons)
  {
    bool should_return = button.isInside(click_pos);
    button.clickInput(click);
    if (should_return)
    {
      return;
    }
  }
}
void LevelEditor::mouseInput(const ASGE::MoveEvent* mouse)
{
  Scene::mouseInput(mouse);
  auto mouse_pos = ASGE::Point2D(static_cast<float>(mouse->xpos), static_cast<float>(mouse->ypos));
  if (mouse_pos.x >= 256 && mouse_pressed)
  {
    auto x_pos = static_cast<size_t>(mouse_pos.x) / 32;
    auto y_pos = static_cast<size_t>(mouse_pos.y) / 32;
    if (x_pos < 50 && y_pos < 50)
    {
      tile_map.setTile(
        0, x_pos + y_pos * 50, "data/images/tilesets/japanese_city.png", tile_set.getCurrentRect());
    }
  }
  cursor.setCursor(Cursor::POINTER);
  for (auto& button : scene_change_buttons)
  {
    button.mouseInput(mouse);
    if (button.isInside(mouse_pos))
    {
      cursor.setCursor(Cursor::SELECT);
    }
  }
  cursor.mouseInput(mouse);
}