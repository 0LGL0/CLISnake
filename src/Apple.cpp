#include "Apple.h"

[[nodiscard]] std::pair<uint16_t, uint16_t> Apple::getNewPos() noexcept {
  const uint16_t linearRandomPos = static_cast<uint16_t>(mDist(mEngine));
  const uint16_t x = linearRandomPos % mW.ws_col;
  const uint16_t y = linearRandomPos / mW.ws_col;

  mCurrentPos = {x, y};

  return {x, y};
}
