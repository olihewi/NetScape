//
// Created by hewis on 01/04/2021.
//

#include "Scenes/LevelEditor.h"

#include "Utilities/FontManager.h"
#include <Engine/FileIO.hpp>
#include <GameObjects/UI/LevelSelector.h>
#include <iostream>
#include <utility>
LevelEditor::LevelEditor(ASGE::Renderer* _renderer, std::function<void(Scenes)> _scene_callback) :
  Scene(std::move(_scene_callback)), renderer(_renderer),
  tile_map(renderer, "data/images/tilesets/dotonbori.png", 3),
  tile_set(renderer, "data/images/tilesets/dotonbori.png"),
  scene_change_buttons(std::array<UIButton, 1>{ UIButton(
    renderer, "data/images/ui/buttons/neon/yellow.png", "Exit", FONTS::ROBOTO,
    [this]() { setScene(Scenes::TITLE); }, std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
    ASGE::Point2D(1920 - 375, 0), ASGE::Point2D(375, 125)) }),
  cursor(renderer, true), tilemap_camera(
                            static_cast<float>(ASGE::SETTINGS.window_width) - 256,
                            static_cast<float>(ASGE::SETTINGS.window_height) - 128)
{
  cursor.zOrder(10);
  tilemap_camera.lookAt(ASGE::Point2D(
    (static_cast<float>(ASGE::SETTINGS.window_width) - 256) / 2,
    (static_cast<float>(ASGE::SETTINGS.window_height) - 128) / 2));
  addObject(std::make_unique<UIButton>(
    renderer,
    "data/images/ui/buttons/neon/green.png",
    "Save",
    FONTS::ROBOTO,
    [this]() { saveLevel("dotonbori.json"); },
    std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
    ASGE::Point2D(1920 - 750),
    ASGE::Point2D(375, 125)));
  addObject(std::make_unique<UIButton>(
    renderer,
    "data/images/ui/buttons/neon/blue.png",
    "Load",
    FONTS::ROBOTO,
    [this]() { loadLevel("userlevels/dotonbori.json"); },
    std::array<float, 6>{ 11, 11, 114, 50, 11, 11 },
    ASGE::Point2D(1920 - 1125),
    ASGE::Point2D(375, 125)));

  addObject(std::make_unique<LevelSelector>(renderer));
}
void LevelEditor::render(ASGE::Renderer* /*renderer*/)
{
  Scene::render(renderer);
  tile_set.render(renderer);
  for (auto& button : scene_change_buttons)
  {
    button.render(renderer);
  }

  auto renderer_view = renderer->getViewport();
  renderer->setViewport(
    { 256, 0, ASGE::SETTINGS.window_width - 256, ASGE::SETTINGS.window_height - 125 });
  renderer->setProjectionMatrix(tilemap_camera.getView());
  tile_map.render(renderer);
  renderer->setViewport(renderer_view);
  renderer->setProjectionMatrix(
    0,
    0,
    static_cast<float>(ASGE::SETTINGS.window_width),
    static_cast<float>(ASGE::SETTINGS.window_height));

  cursor.render(renderer);
}
void LevelEditor::update(InputTracker& input, float dt)
{
  Scene::update(input, dt);
  tile_set.update(input, dt);
  tile_map.update(input, dt);
  cursor.update(input, dt);
  if (input.getKeyDown(ASGE::KEYS::KEY_1))
  {
    current_layer = 0;
  }
  else if (input.getKeyDown(ASGE::KEYS::KEY_2))
  {
    current_layer = 1;
  }
  else if (input.getKeyDown(ASGE::KEYS::KEY_3))
  {
    current_layer = 2;
  }
  auto relative_mouse_pos = input.getMousePos();
  auto camera_view        = tilemap_camera.getView();
  if (relative_mouse_pos.x > 256)
  {
    placeTiles(input, relative_mouse_pos, camera_view);

    auto camera_move = input.getWASD();
    tilemap_camera.translate(camera_move.x * 256 * dt, -camera_move.y * 256 * dt, 0);
    auto camera_scroll = -input.getMouseScroll().y;
    if (std::fabs(camera_scroll) >= 0.5F)
    {
      tilemap_camera.setZoom(tilemap_camera.getZoom() * (camera_scroll / 4 + 1));
    }
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
void LevelEditor::placeTiles(
  InputTracker& input, ASGE::Point2D& relative_mouse_pos,
  const ASGE::Camera::CameraView& camera_view)
{
  relative_mouse_pos.x =
    (relative_mouse_pos.x - 256) * tilemap_camera.getZoom() + camera_view.min_x;
  relative_mouse_pos.y =
    (relative_mouse_pos.y - 125) * tilemap_camera.getZoom() + camera_view.min_y;
  if (relative_mouse_pos.x >= 0 && relative_mouse_pos.y >= 0)
  {
    if (input.getMouseButton(MOUSE::LEFT_CLICK))
    {
      placeTiles(relative_mouse_pos, 0);
    }
    if (input.getMouseButton(MOUSE::RIGHT_CLICK))
    {
      placeTiles(relative_mouse_pos, 1);
    }
    if (input.getMouseButton(MOUSE::MIDDLE_CLICK))
    {
      placeTiles(relative_mouse_pos, 2);
    }
    if (input.getMouseButton(MOUSE::MOUSE_5))
    {
      placeTiles(relative_mouse_pos, 3);
    }
    if (input.getKeyDown(ASGE::KEYS::KEY_L))
    {
      auto x_pos = static_cast<size_t>(relative_mouse_pos.x) / 32;
      auto y_pos = static_cast<size_t>(relative_mouse_pos.y) / 32;
      tile_map.setAnimatedTile(
        current_layer,
        x_pos + y_pos * 50,
        "data/images/animations/japanese_city/crow_ground.png",
        10);
    }
  }
}
void LevelEditor::placeTiles(ASGE::Point2D _position, int _mouse_button)
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
    switch (_mouse_button)
    {
      case 0: /// Add Tile
      {
        tile_map.setTile(current_layer, x_pos + y_pos * 50 + offset_x + offset_y * 50, tile);
        break;
      }
      case 1: /// Remove Tile
      {
        tile_map.deleteTile(current_layer, x_pos + y_pos * 50 + offset_x + offset_y * 50);
        break;
      }
      case 2: /// Add Collision
      {
        tile_map.setCollision(x_pos + y_pos * 50, 1);
        break;
      }
      case 3: /// Remove Collision
      {
        tile_map.setCollision(x_pos + y_pos * 50, 0);
        break;
      }
      default:
      {
        break;
      }
    }
    offset_x++;
    if (offset_x % tiles.selection_width == 0)
    {
      offset_x = 0;
      offset_y++;
    }
  }
}
void LevelEditor::saveLevel(const std::string& file_name)
{
  ASGE::FILEIO::createDir("userlevels");
  ASGE::FILEIO::File file;
  if (file.open("userlevels/" + file_name, ASGE::FILEIO::File::IOMode::WRITE))
  {
    ASGE::FILEIO::IOBuffer buffer = ASGE::FILEIO::IOBuffer();
    std::string j                 = tile_map.saveTileMap().dump(2);
    const auto* as_char           = j.c_str();
    buffer.append(as_char, j.size());
    file.write(buffer);
    std::cout << "Saved Level to %appdata%/ASGE/NetScape/userlevels/" << file_name << std::endl;
  }
  file.close();
}
void LevelEditor::loadLevel(const std::string& file_name)
{
  tile_map = TileMap(renderer, file_name);
  ASGE::FILEIO::File file;
  if (file.open(file_name, ASGE::FILEIO::File::IOMode::READ))
  {
    ASGE::FILEIO::IOBuffer buffer = file.read();
    auto json_file = nlohmann::json::parse(buffer.as_char(), buffer.as_char() + buffer.length);
    file.close();
    tile_set.setTileset(json_file["tileset"].get<std::string>());
  }
}
