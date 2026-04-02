#pragma once

#include <random>
#include <sys/ioctl.h>

class Apple final {
public:
  Apple(const winsize &w) noexcept
      : mEngine(mRandDevice()), mDist(0, w.ws_col * w.ws_row - 1), mW(w),
        mCurrentPos(0, 0) {}
  ~Apple() noexcept = default;

  [[nodiscard]] std::pair<uint16_t, uint16_t> getNewPos() noexcept;

  [[nodiscard]] inline std::pair<uint16_t, uint16_t> getPos() const noexcept {
    return mCurrentPos;
  }

private:
  std::random_device mRandDevice;
  std::mt19937 mEngine;
  std::uniform_int_distribution<> mDist;

  std::pair<uint16_t, uint16_t> mCurrentPos;
  winsize mW;
};
