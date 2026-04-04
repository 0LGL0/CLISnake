#include "Game.h"
#include <thread>

Game::Game() noexcept
    : mApple(mFramebuffer.getWinSize()), mSnake(mFramebuffer.getWinSize()),
      mFrameLock(1000 / 10), mGameIsRunning(true),
      mApplePos(mApple.getNewPos()) {
  mFramebuffer.hideCursor();
}

void Game::gameLoop() noexcept {
  while (mGameIsRunning) {
    mStartTimePoint = std::chrono::steady_clock::now();

    gameInput();
    mSnake.move(mSnake.getCurrentDirection());
    drawInFramebuffer();

    mEndTimePoint = std::chrono::steady_clock::now();
    auto dt = mEndTimePoint - mStartTimePoint;

    if (dt < mFrameLock)
      std::this_thread::sleep_for(mFrameLock - dt);
  }
}

void Game::gameInput() noexcept {
  if (mInput.kbhit()) {
    char input = getchar();
    switch (input) {
      using enum Snake::Direction;
    case 'q':
      mGameIsRunning = false;
      break;
    case 'w':
      mSnake.setNewDirection(Up);
      break;
    case 's':
      mSnake.setNewDirection(Down);
      break;
    case 'a':
      mSnake.setNewDirection(Left);
      break;
    case 'd':
      mSnake.setNewDirection(Right);
      break;
    case 'e':
      mSnake.addTail();
      break;
    }
  }
}

void Game::drawInFramebuffer() noexcept {
  mFramebuffer.clear();

  mFramebuffer.addSym(mApplePos.first, mApplePos.second, '$');
  for (const auto &head : mSnake.getSnakeHeads())
    mFramebuffer.addSym(head.x, head.y, '#');

  const auto snakeHead = mSnake.getSnakeHeads().back();
  if (snakeHead.x == mApple.getPos().first &&
      snakeHead.y == mApple.getPos().second) {
    mApplePos = mApple.getNewPos();
    mSnake.addTail();
  }

  mFramebuffer.draw();
}
