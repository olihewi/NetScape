#include "ASGEGame.hpp"
#include <Engine/Logger.hpp>

int main(int /*argc*/, char* /*argv*/[])
{
  ASGE::GameSettings game_settings;
  game_settings.window_title = "NetScape";

  game_settings.window_width  = 1920;
  game_settings.window_height = 1080;

  game_settings.mode     = ASGE::GameSettings::WindowMode::WINDOWED;
  game_settings.fixed_ts = 1; // We're not using fixed ts so this is to avoid debug messages...

  game_settings.fps_limit  = 120;
  game_settings.msaa_level = 1;

  game_settings.mag_filter = ASGE::GameSettings::MagFilter::NEAREST;

  Logging::INFO("Launching Game!");
  ASGEGame game(game_settings);
  game.run();
  return 0;
}
