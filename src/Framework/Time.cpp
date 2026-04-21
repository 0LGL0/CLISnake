#include "Time.h"
#include <thread>

void Time::setupFrameRateLimit() noexcept {
  mCurrentDeltaTime = mEnd - mStart;
  if (mCurrentDeltaTime < mFrameRateTargetDuration)
    std::this_thread::sleep_for(mFrameRateTargetDuration - mCurrentDeltaTime);
}
