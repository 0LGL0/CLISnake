#pragma once

#include "Apple.h"
#include "Framework/Framebuffer.h"
#include "Framework/Input.h"
#include "Framework/Time.h"

#include "Framework/World.h"

class Game final {
public:
  Game() noexcept;
  ~Game() noexcept = default;

  void gameLoop() noexcept;

private:
  void gameInput() noexcept;
  void drawInFramebuffer() noexcept;

private:
  FrameBuffer mFramebuffer;
  Apple mApple;
  Input mInput;
  Time mTime;

  bool mGameIsRunning;
  std::pair<uint16_t, uint16_t> mApplePos;

  EntityID mSnakeHead;
};
