//
// Created by hewis on 20/04/2021.
//

#ifndef ASGEMOVIEGAME_CONTROLLERDISPLAY_H
#define ASGEMOVIEGAME_CONTROLLERDISPLAY_H

#include <ASGEGameLib/GameObjects/Sprites/Sprite.h>
#include <ASGEGameLib/GameObjects/Sprites/Text.h>
class ControllerDisplay : public GameObject
{
 public:
  ControllerDisplay(
    ASGE::Renderer* renderer, size_t _controller_id, ASGE::Point2D position,
    ASGE::Point2D dimensions = ASGE::Point2D(811, 567));
  void update(InputTracker& input, float dt) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  std::array<Sprite, 16> sprites;
  Text player_no;
  size_t controller_id;
  ASGE::Point2D left_stick_pos;
  ASGE::Point2D right_stick_pos;
  ASGE::Point2D scale;
  bool is_connected = false;
};

#endif // ASGEMOVIEGAME_CONTROLLERDISPLAY_H
