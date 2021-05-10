//
// Created by hewis on 31/03/2021.
//

#ifndef ASGEMOVIEGAME_ANIMATEDSPRITE_H
#define ASGEMOVIEGAME_ANIMATEDSPRITE_H

#include "Sprite.h"

/// Animated Sprites are implemented using a horizontal-only sprite sheet.
/// Each frame of the sprite must be a square with the same width and height.
class AnimatedSprite : public Sprite
{
 public:
  AnimatedSprite(
    ASGE::Renderer* renderer, const std::string& _file_path, float playback_speed = 1,
    ASGE::Point2D position = ASGE::Point2D());
  void update(InputTracker& input, float dt) override;
  void setFrame(size_t frame);
  void setPlaybackSpeed(float _playback_speed);
  [[nodiscard]] const std::string& getFilePath();
  [[nodiscard]] float getPlaybackSpeed();

 private:
  std::string file_path;
  size_t frames;
  float sprite_size;
  float timer = 0;
  float speed = 1;
};

#endif // ASGEMOVIEGAME_ANIMATEDSPRITE_H
