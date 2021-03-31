#include "ASGEGame.hpp"
#include <ASGEGameLib/GComponent.hpp>

/// Initialises the game.
/// Setup your game and initialise the core components.
/// @param settings
ASGEGame::ASGEGame(const ASGE::GameSettings& settings) :
  OGLGame(settings),
  key_callback_id(inputs->addCallbackFnc(ASGE::E_KEY, &ASGEGame::keyHandler, this))
{
  inputs->use_threads = true;
  toggleFPS();
}

/// Destroys the game.
ASGEGame::~ASGEGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
}

/// Processes key inputs.
/// This function is added as a callback to handle the game's
/// keyboard input. For this game, calls to this function
/// are not thread safe, so you may alter the game's state
/// but your code needs to designed to prevent data-races.
/// @param data
/// @see KeyEvent
void ASGEGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
}

/// Updates your game and all it's components.
/// @param us
void ASGEGame::update(const ASGE::GameTime& us)
{
  for (auto& gc : game_components)
  {
    gc->update(us.deltaInSecs());
  }
}

/// Render your game and its scenes here.
void ASGEGame::render() {}

/// Calls to fixedUpdate use the same fixed timestep
/// irrespective of how much time is passed. This allows
/// calculations to resolve correctly and stop physics
/// simulations from imploding
///
/// https://gamedev.stackexchange.com/questions/1589/when-should-i-use-a-fixed-or-variable-time-step
/// "Use variable timesteps for your game and fixed steps for physics"
/// @param us
void ASGEGame::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}
