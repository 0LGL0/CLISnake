#include "Framebuffer.h"

#include <termios.h>

FrameBuffer::FrameBuffer() noexcept {
  ioctl(0, TIOCGWINSZ, &mW);
  mBuffer.resize(mW.ws_col * mW.ws_row, ' ');
}

void FrameBuffer::clear() noexcept {
  std::cout << "\033[2J\033[1;1H" << std::flush;
  clearBuffer();
}

void FrameBuffer::addSym(const unsigned int x, const unsigned int y,
                         const char ch) noexcept {
  if (x < mW.ws_col && y < mW.ws_row)
    mBuffer[y * mW.ws_col + x] = ch;
}

void FrameBuffer::draw() noexcept {
  for (int i = 0; i < mBuffer.size(); i++) {
    std::cout << mBuffer[i];
    if ((i + 1) % mW.ws_col - 1 == 0)
      std::cout << '\n';
  }
  std::cout << std::flush;
}

void FrameBuffer::clearBuffer() noexcept {
  std::fill(mBuffer.begin(), mBuffer.end(), ' ');
}
