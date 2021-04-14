//
// Created by hewis on 01/04/2021.
//

#include "GameObjects/Tilemap/EditorTileSet.h"
#include <cmath>
#include <utility>
EditorTileSet::EditorTileSet(
  ASGE::Renderer* renderer, const std::string& file_path, int _sprite_size) :
  sprite_sheet(renderer, file_path, ASGE::Point2D(0, 64)),
  cursor(
    renderer, "data/images/tilesets/cursor.png", std::array<float, 6>{ 3, 3, 28, 28, 3, 3 },
    ASGE::Point2D(0, 64), ASGE::Point2D(32, 32)),
  sprite_size(_sprite_size)
{
}
void EditorTileSet::render(ASGE::Renderer* renderer)
{
  sprite_sheet.render(renderer);
  cursor.render(renderer);
}
void EditorTileSet::clickInput(const ASGE::ClickEvent* click)
{
  ASGE::Point2D click_pos =
    ASGE::Point2D(static_cast<float>(click->xpos), static_cast<float>(click->ypos));
  if (sprite_sheet.isInside(click_pos) && click->action != ASGE::KEYS::KEY_REPEATED)
  {
    if (click->action == ASGE::KEYS::KEY_PRESSED)
    {
      auto click_x = std::floor(
        (click_pos.x - sprite_sheet.position().x) / sprite_sheet.dimensions().x *
        (sprite_sheet.dimensions().x / static_cast<float>(sprite_size)));
      auto click_y = std::floor(
        (click_pos.y - sprite_sheet.position().y) / sprite_sheet.dimensions().y *
        (sprite_sheet.dimensions().y / static_cast<float>(sprite_size)));
      mouse_held      = true;
      selection_start = static_cast<int>(
        click_x + click_y * (sprite_sheet.dimensions().x / static_cast<float>(sprite_size)));
      selection_end = selection_start;
    }
    updateSelection(click_pos);
  }
  if (click->action == ASGE::KEYS::KEY_RELEASED)
  {
    mouse_held = false;
  }
}
std::array<float, 4> EditorTileSet::getCurrentRect()
{
  int num_horizontal = static_cast<int>(sprite_sheet.dimensions().x) / sprite_size;
  float x = static_cast<float>(selection_start % num_horizontal) * static_cast<float>(sprite_size);
  int row = selection_start / num_horizontal;
  float y = static_cast<float>(row) * static_cast<float>(sprite_size);
  std::array<float, 4> rect{
    x, y, static_cast<float>(sprite_size), static_cast<float>(sprite_size)
  };
  return rect;
}
void EditorTileSet::mouseInput(const ASGE::MoveEvent* mouse)
{
  if (mouse_held)
  {
    updateSelection(
      ASGE::Point2D(static_cast<float>(mouse->xpos), static_cast<float>(mouse->ypos)));
  }
}
void EditorTileSet::updateSelection(ASGE::Point2D mouse_pos)
{
  if (sprite_sheet.isInside(mouse_pos))
  {
    auto grid_x = std::floor(
      (mouse_pos.x - sprite_sheet.position().x) / sprite_sheet.dimensions().x *
      (sprite_sheet.dimensions().x / static_cast<float>(sprite_size)));
    auto grid_y = std::floor(
      (mouse_pos.y - sprite_sheet.position().y) / sprite_sheet.dimensions().y *
      (sprite_sheet.dimensions().y / static_cast<float>(sprite_size)));
    selection_end = static_cast<int>(
      grid_x + grid_y * (sprite_sheet.dimensions().x / static_cast<float>(sprite_size)));
    int cursor_pos_y = (selection_end > selection_start) ? selection_start / 8 * sprite_size - 1
                                                         : selection_end / 8 * sprite_size - 1;
    int cursor_pos_x = (selection_end % 8 > selection_start % 8)
                         ? selection_start % 8 * sprite_size - 1
                         : selection_end % 8 * sprite_size - 1;
    cursor.position(ASGE::Point2D(
      static_cast<float>(cursor_pos_x) + sprite_sheet.position().x,
      static_cast<float>(cursor_pos_y) + sprite_sheet.position().y));
    float cursor_width =
      std::fabs(static_cast<float>(selection_start % 8 - selection_end % 8)) * 32 + 32;
    int selection_vert_height = std::abs(selection_start / 8 - selection_end / 8);
    float cursor_height       = static_cast<float>(selection_vert_height) * 32 + 32;
    cursor.dimensions(ASGE::Point2D(cursor_width, cursor_height));
  }
}
TileSetSelection EditorTileSet::getSelection() const
{
  std::vector<std::array<float, 4>> vector;
  int start_x = selection_start % 8;
  int start_y = selection_start / 8;
  int end_x   = selection_end % 8;
  int end_y   = selection_end / 8;
  if (start_x > end_x)
  {
    std::swap(start_x, end_x);
  }
  if (start_y > end_y)
  {
    std::swap(start_y, end_y);
  }
  for (int y = start_y; y <= end_y; y++)
  {
    for (int x = start_x; x <= end_x; x++)
    {
      vector.emplace_back(std::array<float, 4>{ static_cast<float>(x * sprite_size),
                                                static_cast<float>(y * sprite_size),
                                                static_cast<float>(sprite_size),
                                                static_cast<float>(sprite_size) });
    }
  }
  return TileSetSelection(vector, static_cast<size_t>(end_x - start_x + 1));
}
TileSetSelection::TileSetSelection(std::vector<std::array<float, 4>> _tiles, size_t _width) :
  tiles(std::move(_tiles)), selection_width(_width)
{
}
