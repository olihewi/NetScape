//
// Created by hewis on 20/04/2021.
//

#include "GameObjects/UI/ControllerDisplay.h"
#include "ASGEGameLib/Utilities/FontManager.h"
ControllerDisplay::ControllerDisplay(
  ASGE::Renderer* renderer, size_t _controller_id, ASGE::Point2D position,
  ASGE::Point2D dimensions) :
  sprites(
    std::array<Sprite, 16>{ Sprite(renderer, "data/images/ui/controller/outline.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position),
                            Sprite(renderer, "data/images/ui/controller/buttons.png", position) }),
  player_no(
    renderer, "Press Any Button", ASGE::Point2D(), FONTS::ROBOTO, ASGE::COLOURS::WHITE, 0.75F),
  controller_id(_controller_id), scale(ASGE::Point2D(dimensions.x / 811, dimensions.y / 567))
{
  sprites[0].dimensions(dimensions);
  sprites[0].srcRect(0, 0, 811, 567);
  sprites[1].srcRect(0, 0, 64, 64); /// A
  sprites[1].dimensions(ASGE::Point2D(64 * scale.x, 64 * scale.y));
  sprites[1].translate(ASGE::Point2D(585 * scale.x, 180 * scale.y));
  sprites[2].srcRect(64, 0, 64, 64); /// B
  sprites[2].dimensions(ASGE::Point2D(64 * scale.x, 64 * scale.y));
  sprites[2].translate(ASGE::Point2D(640 * scale.x, 125 * scale.y));
  sprites[3].srcRect(128, 0, 64, 64); /// X
  sprites[3].dimensions(ASGE::Point2D(64 * scale.x, 64 * scale.y));
  sprites[3].translate(ASGE::Point2D(530 * scale.x, 125 * scale.y));
  sprites[4].srcRect(192, 0, 64, 64); /// Y
  sprites[4].dimensions(ASGE::Point2D(64 * scale.x, 64 * scale.y));
  sprites[4].translate(ASGE::Point2D(585 * scale.x, 70 * scale.y));
  sprites[5].srcRect(256, 206, 172, 63); /// Left Shoulder
  sprites[5].dimensions(ASGE::Point2D(172 * scale.x, 63 * scale.y));
  sprites[5].translate(ASGE::Point2D(127 * scale.x, 6 * scale.y));
  sprites[6].srcRect(256, 80, 172, 63); /// Right Shoulder
  sprites[6].dimensions(ASGE::Point2D(172 * scale.x, 63 * scale.y));
  sprites[6].translate(ASGE::Point2D(513 * scale.x, 6 * scale.y));
  sprites[7].srcRect(256, 0, 40, 40); /// Back
  sprites[7].dimensions(ASGE::Point2D(40 * scale.x, 40 * scale.y));
  sprites[7].translate(ASGE::Point2D(330 * scale.x, 140 * scale.y));
  sprites[8].srcRect(296, 0, 40, 40); /// Start
  sprites[8].dimensions(ASGE::Point2D(40 * scale.x, 40 * scale.y));
  sprites[8].translate(ASGE::Point2D(445 * scale.x, 140 * scale.y));
  sprites[9].srcRect(0, 128, 120, 120); /// Left Stick
  sprites[9].dimensions(ASGE::Point2D(120 * scale.x, 120 * scale.y));
  sprites[9].translate(ASGE::Point2D(140 * scale.x, 100 * scale.y));
  sprites[10].srcRect(0, 128, 120, 120); /// Right Stick
  sprites[10].dimensions(ASGE::Point2D(120 * scale.x, 120 * scale.y));
  sprites[10].translate(ASGE::Point2D(455 * scale.x, 220 * scale.y));
  sprites[11].srcRect(120, 128, 47, 41); /// D-Pad Up
  sprites[11].dimensions(ASGE::Point2D(47 * scale.x, 41 * scale.y));
  sprites[11].translate(ASGE::Point2D(275 * scale.x, 225 * scale.y));
  sprites[12].srcRect(161, 210, 40, 47); /// D-Pad Right
  sprites[12].dimensions(ASGE::Point2D(40 * scale.x, 47 * scale.y));
  sprites[12].translate(ASGE::Point2D(322 * scale.x, 266 * scale.y));
  sprites[13].srcRect(167, 128, 47, 41); /// D-Pad Down
  sprites[13].dimensions(ASGE::Point2D(47 * scale.x, 41 * scale.y));
  sprites[13].translate(ASGE::Point2D(275 * scale.x, 313 * scale.y));
  sprites[14].srcRect(120, 210, 40, 47); /// D-Pad Left
  sprites[14].dimensions(ASGE::Point2D(40 * scale.x, 47 * scale.y));
  sprites[14].translate(ASGE::Point2D(235 * scale.x, 266 * scale.y));
  sprites[15].srcRect(202, 210, 47, 47); /// D-Pad Centre
  sprites[15].dimensions(ASGE::Point2D(47 * scale.x, 47 * scale.y));
  sprites[15].translate(ASGE::Point2D(275 * scale.x, 266 * scale.y));

  left_stick_pos  = sprites[9].position();
  right_stick_pos = sprites[10].position();
  player_no.centrePos(ASGE::Point2D(
    sprites[0].position().x + sprites[0].dimensions().x / 2,
    sprites[0].position().y + sprites[0].dimensions().y / 3.25F));
}
void ControllerDisplay::update(InputTracker& input, float /*dt*/)
{
  if (input.isControllerConnected(controller_id) != is_connected)
  {
    is_connected = !is_connected;
    sprites[0].srcRect((is_connected ? 811.0F : 0.0F), 0, 811, 567);
    player_no.contents(is_connected ? std::to_string(controller_id + 1) : "Press Any Button");
    player_no.centrePos(ASGE::Point2D(
      sprites[0].position().x + sprites[0].dimensions().x / 2,
      sprites[0].position().y + sprites[0].dimensions().y / 3.25F));
  }
  for (size_t i = 0; i < 14; i++)
  {
    if (
      input.getControllerButtonDown(controller_id, i) ||
      input.getControllerButtonUp(controller_id, i))
    {
      auto rect = sprites[i + 1].srcRect();
      sprites[i + 1].srcRect(
        rect[0],
        rect[1] + (input.getControllerButton(controller_id, i) ? rect[3] : -rect[3]),
        rect[2],
        rect[3]);
    }
  }
  auto left_stick = input.getControllerStick(controller_id, 0);
  sprites[9].position(ASGE::Point2D(
    left_stick_pos.x + left_stick.x * 30 * scale.x,
    left_stick_pos.y + left_stick.y * 30 * scale.y));
  auto right_stick = input.getControllerStick(controller_id, 1);
  sprites[10].position(ASGE::Point2D(
    right_stick_pos.x + right_stick.x * 30 * scale.x,
    right_stick_pos.y + right_stick.y * 30 * scale.y));
}
void ControllerDisplay::render(ASGE::Renderer* renderer)
{
  if (is_connected)
  {
    for (auto& sprite : sprites)
    {
      sprite.render(renderer);
    }
  }
  else
  {
    sprites[0].render(renderer);
  }
  player_no.render(renderer);
}
