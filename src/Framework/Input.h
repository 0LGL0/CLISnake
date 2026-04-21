#pragma once

#include <termios.h>

class Input final {
public:
  explicit Input() noexcept { setupNewTerminalMode(); }
  ~Input() noexcept { resetTerminalMode(); }

  [[nodiscard]] bool kbhit() noexcept;
  [[nodiscard]] int getPressedKey() noexcept;

private:
  void setupNewTerminalMode() noexcept;

  void resetTerminalMode() noexcept;

  struct termios mStoredMode{};
  int mOldf = 0;
  bool mHasBufferedKey = false;
  char mBufferedKey = 0;
};
