#include "ASGEGame.hpp"
#include <ASGEGameLib/Scenes/CreditsScene.h>
#include <ASGEGameLib/Scenes/GameScene.h>
#include <ASGEGameLib/Scenes/LevelEditor.h>
#include <ASGEGameLib/Scenes/OptionsScene.h>
#include <ASGEGameLib/Scenes/TestScene.h>
#include <ASGEGameLib/Scenes/TitleScene.h>
#include <ASGEGameLib/Utilities/FontManager.h>

/// Initialises the game
ASGEGame::ASGEGame(const ASGE::GameSettings& settings) :
  OGLGame(settings), input_tracker(inputs.get())
{
  inputs->use_threads = true;
  FontManager::loadFonts(renderer.get());
  setScene(Scene::TITLE);
  inputs->setCursorMode(ASGE::MOUSE::CursorMode::HIDDEN);
}

/// Fixed Update
void ASGEGame::update(const ASGE::GameTime& /*us*/)
{
  // auto dt = static_cast<float>(us.deltaInSecs());
  // scene->update(input_tracker, dt);
}

/// Render and Standard Update
void ASGEGame::render(const ASGE::GameTime& us)
{
  auto dt = static_cast<float>(us.deltaInSecs());
  scene->update(input_tracker, dt);
  scene->render(renderer.get());
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
    case Scene::GAME:
    {
      scene = std::make_unique<GameScene>(renderer.get(), [this](auto&& PH1) { setScene(PH1); });
      break;
    }
    case Scene::LEVEL_EDITOR:
    {
      scene = std::make_unique<LevelEditor>(renderer.get(), [this](auto&& PH1) { setScene(PH1); });
      break;
    }
    case Scene::OPTIONS:
    {
      scene = std::make_unique<OptionsScene>(renderer.get(), [this](auto&& PH1) { setScene(PH1); });
      break;
    }
    case Scene::CREDITS:
    {
      scene = std::make_unique<CreditsScene>(renderer.get(), [this](auto&& PH1) { setScene(PH1); });
      break;
    }
    case Scene::QUIT_GAME:
      signalExit();
      break;
  }
}
