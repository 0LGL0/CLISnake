#include <thread>

#include "src/Apple.h"
#include "src/Framebuffer.h"
#include "src/Input.h"
#include "src/Snake.h"

int main() {
  bool isRunning = true;
  FrameBuffer framebuffer;
  Snake snake{framebuffer.getWinSize()};
  Apple apple{framebuffer.getWinSize()};
  Input input;
  framebuffer.hideCursor();
  std::chrono::time_point<std::chrono::steady_clock> start{}, end{};

  constexpr std::chrono::milliseconds frameLock(1000 / 1);
  unsigned long long frame = 0;

  auto applePos = apple.getNewPos();

  while (isRunning) {
    start = std::chrono::steady_clock::now();
    frame++;

    if (input.kbhit()) {
      char input = getchar();
      switch (input) {
        using enum Snake::Direction;
      case 'q':
        isRunning = false;
        break;
      case 'w':
        snake.move(Up);
        break;
      case 's':
        snake.move(Down);
        break;
      case 'a':
        snake.move(Left);
        break;
      case 'd':
        snake.move(Right);
        break;
      case 'e':
        snake.addTail();
        break;
      }
    }

    framebuffer.clear();
    snake.move(snake.getCurrentDirection());

    framebuffer.addSym(applePos.first, applePos.second, '$');
    for (const auto &head : snake.getSnakeHeads())
      framebuffer.addSym(head.x, head.y, '#');

    const auto snakeHead = snake.getSnakeHeads().back();
    if (snakeHead.x == apple.getPos().first &&
        snakeHead.y == apple.getPos().second) {
      applePos = apple.getNewPos();
      snake.addTail();
    }

    framebuffer.draw();

    end = std::chrono::steady_clock::now();
    auto dt = end - start;
    if (dt < frameLock) {
      std::this_thread::sleep_for(frameLock - dt);
    }
  }
  return 0;
}
