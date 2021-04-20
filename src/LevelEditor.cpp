//
// Created by hewis on 01/04/2021.
//

#include "Scenes/LevelEditor.h"

#include "Utilities/FontManager.h"
#include <Engine/FileIO.h>
#include <iostream>
#include <utility>
LevelEditor::LevelEditor(ASGE::Renderer* _renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), renderer(_renderer),
  tile_map(renderer, "data/images/tilesets/japanese_city.png", 2),
  tile_set(renderer, "data/images/tilesets/japanese_city.png"),
  scene_change_buttons(std::array<UIButton, 1>{ UIButton(
    renderer, "data/images/ui/buttons/neon/yellow.png", "Exit", FONTS::ROBOTO,
    [this]() { setScene(Scenes::TITLE); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
    ASGE::Point2D(1920 - 375, 0), ASGE::Point2D(375, 125)) }),
  cursor(renderer, true)
{
}
void LevelEditor::render(ASGE::Renderer* /*renderer*/)
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
void LevelEditor::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);
  tile_set.update(input, dt);
  cursor.update(input, dt);
  if (input.getKeyDown(ASGE::KEYS::KEY_1))
  {
    current_layer = 0;
  }
  else if (input.getKeyDown(ASGE::KEYS::KEY_2))
  {
    current_layer = 1;
  }
  if (input.getMouseButton(MOUSE::LEFT_CLICK))
  {
    placeTiles(input.getMousePos());
  }
  if (input.getMouseButton(MOUSE::RIGHT_CLICK))
  {
    auto mouse_pos = input.getMousePos();
    auto x_pos     = static_cast<size_t>(mouse_pos.x) / 32;
    auto y_pos     = static_cast<size_t>(mouse_pos.y) / 32;
    if (mouse_pos.x >= 256)
    {
      tile_map.deleteTile(current_layer, x_pos + y_pos * 50);
    }
  }
  if (input.getKeyDown(ASGE::KEYS::KEY_S))
  {
    saveLevel("dotonbori.json");
  }
  if (input.getKeyDown(ASGE::KEYS::KEY_L))
  {
    loadLevel("levels/dotonbori.json");
  }
  cursor.setCursor(Cursor::POINTER);
  for (auto& button : scene_change_buttons)
  {
    bool should_return = button.isInside(input.getMousePos());
    if (should_return)
    {
      cursor.setCursor(Cursor::SELECT);
    }
    button.update(input, dt);
    if (should_return && input.getMouseButton(MOUSE::LEFT_CLICK))
    {
      return;
    }
  }
}
void LevelEditor::placeTiles(ASGE::Point2D _position)
{
  if (_position.x >= 256)
  {
    auto x_pos      = static_cast<size_t>(_position.x) / 32;
    auto y_pos      = static_cast<size_t>(_position.y) / 32;
    auto tiles      = tile_set.getSelection();
    size_t offset_x = 0;
    size_t offset_y = 0;
    for (auto& tile : tiles.tiles)
    {
      if (x_pos + offset_x >= 50 || y_pos + offset_y >= 50)
      {
        continue;
      }
      tile_map.setTile(current_layer, x_pos + y_pos * 50 + offset_x + offset_y * 50, tile);
      offset_x++;
      if (offset_x % tiles.selection_width == 0)
      {
        offset_x = 0;
        offset_y++;
      }
    }
  }
}
void LevelEditor::saveLevel(const std::string& file_name)
{
  ASGE::FILEIO::createDir("levels");
  ASGE::FILEIO::File file;
  if (file.open("levels/" + file_name, ASGE::FILEIO::File::IOMode::WRITE))
  {
    ASGE::FILEIO::IOBuffer buffer = ASGE::FILEIO::IOBuffer();
    std::string j                 = tile_map.saveTileMap().dump();
    const auto* as_char           = j.c_str();
    buffer.append(as_char, j.size());
    file.write(buffer);
    std::cout << "Saved Level to %appdata%/ASGE/NetScape/" << file_name << std::endl;
  }
  file.close();
}
void LevelEditor::loadLevel(const std::string& file_name)
{
  tile_map = TileMap(renderer, file_name);
}
