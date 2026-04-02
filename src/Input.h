#pragma once

#include <termios.h>

class Input final {
public:
  explicit Input() noexcept { setupNewTerminalMode(); }
  ~Input() noexcept { resetTerminalMode(); }

  int kbhit() noexcept;

private:
  void setupNewTerminalMode() noexcept;

  void resetTerminalMode() noexcept;

  struct termios storedMode{};
};
