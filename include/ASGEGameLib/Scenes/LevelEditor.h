//
// Created by hewis on 01/04/2021.
//

#ifndef ASGEMOVIEGAME_LEVELEDITOR_H
#define ASGEMOVIEGAME_LEVELEDITOR_H

#include "Scene.h"
#include <ASGEGameLib/GameObjects/Tilemap/EditorTileSet.h>
#include <ASGEGameLib/GameObjects/Tilemap/TileMap.h>
#include <ASGEGameLib/GameObjects/UI/Cursor.h>
#include <ASGEGameLib/GameObjects/UI/UIButton.h>
class LevelEditor : public Scene
{
 public:
  explicit LevelEditor(ASGE::Renderer* renderer, std::function<void(Scenes)> _scene_callback);
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  void placeTiles(ASGE::Point2D _position);
  TileMap tile_map;
  EditorTileSet tile_set;
  std::array<UIButton, 1> scene_change_buttons;
  Cursor cursor;
};

#endif // ASGEMOVIEGAME_LEVELEDITOR_H
