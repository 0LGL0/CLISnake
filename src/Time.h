#pragma once

#include <chrono>
#include <ratio>

class Time final {
public:
  Time() noexcept
      : mFrameRateTargetDuration(1'000'000'000 / mFrameRateTarget) {}
  ~Time() noexcept = default;

  inline void setEndOfGameLoopTimePoint() noexcept {
    mEnd = std::chrono::steady_clock::now();
  }

  inline void setStartOfGameLoopTimePoint() noexcept {
    mStart = std::chrono::steady_clock::now();
  }

  inline void setFrameRateTarget(unsigned int target) noexcept {
    mFrameRateTarget = target;
  }

  [[nodiscard]] inline long getCurrentDeltaTime() const noexcept {
    return (mEnd - mStart).count();
  }

  void setupFrameRateLimit() noexcept;

private:
  std::chrono::steady_clock::time_point mStart, mEnd;

  unsigned int mFrameRateTarget = 10;
  std::chrono::nanoseconds mFrameRateTargetDuration;
  std::chrono::nanoseconds mCurrentDeltaTime;
};
