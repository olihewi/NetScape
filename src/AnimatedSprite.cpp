//
// Created by hewis on 31/03/2021.
//

#include "GameObjects/Sprites/AnimatedSprite.h"
#include <cmath>
AnimatedSprite::AnimatedSprite(
  ASGE::Renderer* renderer, const std::string& file_path, float playback_speed,
  ASGE::Point2D position) :
  Sprite(renderer, file_path, position),
  speed(playback_speed)
{
  auto dims   = Sprite::dimensions();
  frames      = static_cast<size_t>(dims.x) / static_cast<size_t>(dims.y);
  sprite_size = dims.y;
  Sprite::srcRect(0, 0, dims.y, dims.y);
  Sprite::dimensions(ASGE::Point2D(dims.y, dims.y));
}
void AnimatedSprite::update(InputTracker& /*input*/, float dt)
{
  timer            = std::fmod(timer + dt, static_cast<float>(frames) / speed);
  float this_frame = std::floor(timer * speed);
  Sprite::srcRect(this_frame * sprite_size, 0, sprite_size, sprite_size);
}
void AnimatedSprite::setFrame(size_t frame)
{
  Sprite::srcRect(static_cast<float>(frame) * sprite_size, 0, sprite_size, sprite_size);
  size_t frame_proportion = frame / frames;
  timer                   = static_cast<float>(frame_proportion) * speed;
}
void AnimatedSprite::setPlaybackSpeed(float _playback_speed)
{
  speed = _playback_speed;
}
