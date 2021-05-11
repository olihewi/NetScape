//
// Created by hewis on 31/03/2021.
//

#include "GameObjects/Sprites/AnimatedSprite.h"
#include <cmath>
AnimatedSprite::AnimatedSprite(
  ASGE::Renderer* renderer, const std::string& _file_path, float playback_speed,
  ASGE::Point2D position) :
  Sprite(renderer, _file_path, position),
  file_path(_file_path),
  frames(static_cast<size_t>(Sprite::dimensions().x) / static_cast<size_t>(Sprite::dimensions().y)),
  sprite_size(Sprite::dimensions().y), speed(playback_speed)
{
  auto dims = Sprite::dimensions();
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
const std::string& AnimatedSprite::getFilePath()
{
  return file_path;
}
float AnimatedSprite::getPlaybackSpeed() const
{
  return speed;
}
void AnimatedSprite::loadAnimation(
  ASGE::Renderer* renderer, const std::string& _file_path, float playback_speed)
{
  Sprite::loadSprite(renderer, _file_path);
  file_path   = _file_path;
  auto dims   = Sprite::dimensions();
  frames      = static_cast<size_t>(dims.x) / static_cast<size_t>(dims.y);
  sprite_size = dims.y;
  timer       = 0;
  speed       = playback_speed;
  Sprite::srcRect(0, 0, dims.y, dims.y);
  Sprite::dimensions(ASGE::Point2D(dims.y, dims.y));
}
