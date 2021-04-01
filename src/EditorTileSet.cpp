//
// Created by hewis on 01/04/2021.
//

#include "GameObjects/Tilemap/EditorTileSet.h"
#include <cmath>
EditorTileSet::EditorTileSet(
  ASGE::Renderer* renderer, const std::string& file_path, int _sprite_size) :
  sprite_sheet(renderer, file_path, ASGE::Point2D(0, 64)),
  cursor(
    renderer, "data/images/tilesets/cursor.png", std::array<float, 6>{ 3, 3, 28, 28, 3, 3 },
    ASGE::Point2D(), ASGE::Point2D(32, 32)),
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
    auto click_x = std::floor(
      (click_pos.x - sprite_sheet.position().x) / sprite_sheet.dimensions().x *
      (sprite_sheet.dimensions().x / static_cast<float>(sprite_size)));
    auto click_y = std::floor(
      (click_pos.y - sprite_sheet.position().y) / sprite_sheet.dimensions().y *
      (sprite_sheet.dimensions().y / static_cast<float>(sprite_size)));
    if (click->action == ASGE::KEYS::KEY_PRESSED)
    {
      selection_start = static_cast<int>(
        click_x + click_y * (sprite_sheet.dimensions().x / static_cast<float>(sprite_size)));
      selection_end = selection_start;
    }
    else if (click->action == ASGE::KEYS::KEY_RELEASED)
    {
      selection_end = static_cast<int>(
        click_x + click_y * (sprite_sheet.dimensions().x / static_cast<float>(sprite_size)));
    }
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
