//
// Created by hewis on 13/04/2021.
//

#ifndef ASGEMOVIEGAME_SOUND_H
#define ASGEMOVIEGAME_SOUND_H

#include <soloud_wav.h>
#include <string>
class Sound
{
 public:
  Sound(SoLoud::Soloud* _engine, const std::string& file_path);
  SoLoud::Wav& getSound();
  void play();
  void stop();
  void volume(float _volume);
  void setLoop(bool _loop);
  void setSpeed(float _speed);

  void setSound(std::string& file_path);
 private:
  SoLoud::Soloud* engine;
  SoLoud::Wav clip;
  SoLoud::handle handle = UINT16_MAX;
};

#endif // ASGEMOVIEGAME_SOUND_H
