#pragma once

#include <iostream>
#include <sys/ioctl.h>
#include <vector>

class FrameBuffer final {
public:
  explicit FrameBuffer() noexcept;
  ~FrameBuffer() noexcept = default;

  void clear() noexcept;

  void inline hideCursor() noexcept { std::cout << "\e[?25l"; }

  void addSym(const unsigned int x, const unsigned int y,
              const char ch) noexcept;
  void draw() noexcept;
  [[nodiscard]] inline const winsize &getWinSize() const noexcept { return mW; }

private:
  void clearBuffer() noexcept;
  winsize mW{};
  std::vector<char> mBuffer;
};
