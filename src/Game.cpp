#include "Game.h"
#include "Components/SnakeHeadComponent.h"
#include "Components/SnakeSegmentComponent.h"
#include "Framework/Components/TransformComponent.h"
#include "Framework/Components/VelocityComponent.h"
#include "Framework/EngineManager.h"
#include "Framework/Systems/MovementSystem.h"
#include "SnakeFactory.h"
#include "Systems/SnakeMovementSystem.h"

Game::Game() noexcept
    : mApple(mFramebuffer.getWinSize()), mGameIsRunning(true),
      mApplePos(mApple.getNewPos()) {
  mFramebuffer.hideCursor();
  mTime.setFrameRateTarget(10);

  auto &sceneManager = EngineManager::getInstance().getSceneManager();
  auto scene = sceneManager.createNewScene();
  sceneManager.setCurrentScene(scene);

  scene->getWorld().getSystemManager().registryNewSystem<SnakeMovementSystem>(
      SystemPriority::Physics);

  const winsize &ws = mFramebuffer.getWinSize();
  mSnakeHead = SnakeFactory::spawn(*scene, static_cast<int>(ws.ws_col) / 2,
                                   static_cast<int>(ws.ws_row) / 2);
}

void Game::gameLoop() noexcept {
  auto scene = EngineManager::getInstance().getSceneManager().getCurrentScene();
  while (mGameIsRunning) {
    mTime.setStartOfGameLoopTimePoint();

    gameInput();
    scene->update(static_cast<double>(mTime.getCurrentDeltaTime()));
    drawInFramebuffer();

    mTime.setEndOfGameLoopTimePoint();
    mTime.setupFrameRateLimit();
  }
}

void Game::gameInput() noexcept {
  if (!mInput.kbhit())
    return;

  auto *scene =
      EngineManager::getInstance().getSceneManager().getCurrentScene();
  auto &registry = scene->getWorld().getRegistry();
  auto &head = registry.get<SnakeHeadComponent>(mSnakeHead);

  switch (mInput.getPressedKey()) {
    using enum SnakeDirection;
  case 'q':
    mGameIsRunning = false;
    break;
  case 'w':
    head.direction = Up;
    break;
  case 's':
    head.direction = Down;
    break;
  case 'a':
    head.direction = Left;
    break;
  case 'd':
    head.direction = Right;
    break;
  case 'e':
    SnakeFactory::addTail(*scene, mSnakeHead);
    break;
  }
}

void Game::drawInFramebuffer() noexcept {
  auto scene = EngineManager::getInstance().getSceneManager().getCurrentScene();
  auto &registry = scene->getWorld().getRegistry();

  mFramebuffer.clear();

  mFramebuffer.addSym(mApplePos.first, mApplePos.second, '$');

  auto view = registry.view<SnakeSegmentComponent, TransformComponent>();
  for (auto entity : view) {
    const auto &trans = registry.get<TransformComponent>(entity);
    mFramebuffer.addSym(static_cast<unsigned int>(trans.position.x),
                        static_cast<unsigned int>(trans.position.y), '#');
  }

  const auto &headTrans = registry.get<TransformComponent>(mSnakeHead);
  if (static_cast<uint16_t>(headTrans.position.x) == mApplePos.first &&
      static_cast<uint16_t>(headTrans.position.y) == mApplePos.second) {
    mApplePos = mApple.getNewPos();
    SnakeFactory::addTail(*scene, mSnakeHead);
  }

  mFramebuffer.draw();
}
