//
// Created by hewis on 13/04/2021.
//

#include "ASGEGameLib/Utilities/Sound.h"
#include <Engine/FileIO.h>
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
  engine->play(clip);
}
