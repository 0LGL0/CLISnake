#include "Input.h"

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

int Input::kbhit() noexcept {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

void Input::setupNewTerminalMode() noexcept {
  struct termios newMode{};
  tcgetattr(0, &storedMode);
  newMode = storedMode;

  newMode.c_lflag &= (~ICANON);
  newMode.c_lflag &= (~ECHO);
  newMode.c_cc[VTIME] = 0;
  newMode.c_cc[VMIN] = 1;

  tcsetattr(0, TCSANOW, &newMode);
}

void Input::resetTerminalMode() noexcept { tcsetattr(0, TCSANOW, &storedMode); }
