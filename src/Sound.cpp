//
// Created by hewis on 13/04/2021.
//

#include "ASGEGameLib/Utilities/Sound.h"
#include <Engine/FileIO.hpp>
Sound::Sound(SoLoud::Soloud* _engine, const std::string& file_path) : engine(_engine)
{
  ASGE::FILEIO::File file;
  if (file.open(file_path))
  {
    auto io_buffer = file.read();
    clip.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
}
SoLoud::Wav& Sound::getSound()
{
  return clip;
}
void Sound::play()
{
  handle = engine->play(clip);
}

void Sound::stop()
{
  engine->stopAudioSource(clip);
}
void Sound::volume(float _volume)
{
  clip.setVolume(_volume);
  engine->setVolume(handle, _volume);
}
void Sound::setLoop(bool _loop)
{
  clip.setLooping(_loop);
  engine->setLooping(handle, _loop);
}
void Sound::setSpeed(float _speed)
{
  engine->setRelativePlaySpeed(handle, _speed);
}
void Sound::setSound(std::string& file_path)
{
  ASGE::FILEIO::File file;
  if (file.open(file_path))
  {
    auto io_buffer = file.read();
    clip.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
}
