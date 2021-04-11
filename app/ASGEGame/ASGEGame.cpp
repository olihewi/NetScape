#include "ASGEGame.hpp"
#include <ASGEGameLib/Scenes/LevelEditor.h>
#include <ASGEGameLib/Scenes/TitleScene.h>
#include <ASGEGameLib/Utilities/FontManager.h>

/// Initialises the game
ASGEGame::ASGEGame(const ASGE::GameSettings& settings) :
  OGLGame(settings),
  key_callback_id(inputs->addCallbackFnc(ASGE::E_KEY, &ASGEGame::keyHandler, this)),
  click_callback_id(inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &ASGEGame::clickHandler, this)),
  mouse_callback_id(inputs->addCallbackFnc(ASGE::E_MOUSE_MOVE, &ASGEGame::mouseHandler, this)),
  scroll_callback_id(inputs->addCallbackFnc(ASGE::E_MOUSE_SCROLL, &ASGEGame::scrollHandler, this))
{
  inputs->use_threads = true;
  toggleFPS();
  FontManager::loadFonts(renderer.get());
  setScene(Scene::LEVEL_EDITOR);
  setScene(Scene::TITLE);
}

/// Destroys the game
ASGEGame::~ASGEGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(click_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(mouse_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(scroll_callback_id));
}

/// Processes key inputs
void ASGEGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
  scene->keyInput(key);
}
/// Processes mouse clicks
void ASGEGame::clickHandler(ASGE::SharedEventData data)
{
  const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());
  scene->clickInput(click);
}
/// Processes mouse movement
void ASGEGame::mouseHandler(ASGE::SharedEventData data)
{
  const auto* mouse = dynamic_cast<const ASGE::MoveEvent*>(data.get());
  scene->mouseInput(mouse);
}
/// Processes mouse scrolling
void ASGEGame::scrollHandler(ASGE::SharedEventData data)
{
  const auto* scroll = dynamic_cast<const ASGE::ScrollEvent*>(data.get());
  scene->scrollInput(scroll);
}
/// Updates the current scene every frame
void ASGEGame::update(const ASGE::GameTime& us)
{
  auto dt = static_cast<float>(us.deltaInSecs());
  scene->update(dt);
}

/// Renders the current scene
void ASGEGame::render()
{
  scene->render(renderer.get());
}

/// Fixed Update can be used for physics stuff
void ASGEGame::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}
void ASGEGame::setScene(Scene::Scenes _scene)
{
  scene = nullptr;
  switch (_scene)
  {
    case Scene::TITLE:
    {
      scene = std::make_unique<TitleScene>(renderer.get(), [this](auto&& PH1) { setScene(PH1); });
      break;
    }
    case Scene::LEVEL_EDITOR:
    {
      scene = std::make_unique<LevelEditor>(renderer.get(), [this](auto&& PH1) { setScene(PH1); });
      break;
    }
    case Scene::QUIT_GAME:
      signalExit();
      break;
  }
}
