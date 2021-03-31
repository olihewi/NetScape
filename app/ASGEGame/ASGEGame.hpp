//
// Created by huxy on 23/02/2020.
//

#pragma once

#include <ASGEGameLib/Scenes/Scene.h>
#include <Engine/OGLGame.h>
#include <vector>

class ASGEGame : public ASGE::OGLGame
{
 public:
  explicit ASGEGame(const ASGE::GameSettings& settings);
  ~ASGEGame() override;

  ASGEGame(const ASGEGame&) = delete;
  ASGEGame& operator=(const ASGEGame&) = delete;

  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void mouseHandler(ASGE::SharedEventData data);
  void scrollHandler(ASGE::SharedEventData data);

  void update(const ASGE::GameTime& us) override;
  void render() override;
  void fixedUpdate(const ASGE::GameTime& us) override;

 private:
  std::unique_ptr<Scene> scene;
  /// Callback IDs are used to unregister the callback when the game is closed.
  int key_callback_id    = -1;
  int click_callback_id  = -1;
  int mouse_callback_id  = -1;
  int scroll_callback_id = -1;
};
