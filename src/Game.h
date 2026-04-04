#pragma once

#include "Apple.h"
#include "Framebuffer.h"
#include "Input.h"
#include "Snake.h"

#include <chrono>

class Game final {
public:
  Game() noexcept;
  ~Game() noexcept = default;

  void gameLoop() noexcept;

private:
  void gameInput() noexcept;
  void drawInFramebuffer() noexcept;

  FrameBuffer mFramebuffer;
  Snake mSnake;
  Apple mApple;
  Input mInput;

  std::chrono::time_point<std::chrono::steady_clock> mStartTimePoint{},
      mEndTimePoint{};
  std::chrono::milliseconds mFrameLock;

  bool mGameIsRunning;
  std::pair<uint16_t, uint16_t> mApplePos;
};
