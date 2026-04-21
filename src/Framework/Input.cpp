#include "Input.h"

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

bool Input::kbhit() noexcept {
  if (mHasBufferedKey)
    return true;

  char ch;
  ssize_t n = read(STDIN_FILENO, &ch, 1);

  if (n > 0) {
    mBufferedKey = ch;
    mHasBufferedKey = true;
    return true;
  }
  return false;
}

int Input::getPressedKey() noexcept {
  if (mHasBufferedKey) {
    mHasBufferedKey = false;
    return static_cast<unsigned char>(mBufferedKey);
  }
  return 0;
}

void Input::setupNewTerminalMode() noexcept {
  struct termios newMode{};
  tcgetattr(0, &mStoredMode);
  newMode = mStoredMode;

  newMode.c_lflag &= ~(ICANON | ECHO);
  newMode.c_cc[VTIME] = 0;
  newMode.c_cc[VMIN] = 0;

  tcsetattr(0, TCSANOW, &newMode);

  mOldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, mOldf | O_NONBLOCK);
}

void Input::resetTerminalMode() noexcept {
  tcsetattr(0, TCSANOW, &mStoredMode);
  fcntl(STDIN_FILENO, F_SETFL, mOldf);
}
