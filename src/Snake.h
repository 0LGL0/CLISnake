#pragma once

#include <list>
#include <sys/ioctl.h>

struct SnakeHead final {
  unsigned int x = 0, y = 0;
  explicit SnakeHead(unsigned int x, unsigned int y) noexcept : x(x), y(y) {}
  ~SnakeHead() noexcept = default;
};

struct Snake final {
  enum class Direction { Up, Down, Left, Right };

  explicit Snake(const winsize &w) noexcept;
  ~Snake() noexcept = default;

  [[nodiscard]] inline const std::list<SnakeHead> &
  getSnakeHeads() const noexcept {
    return mSnake;
  }

  [[nodiscard]] inline const Direction &getCurrentDirection() const noexcept {
    return mMoveDirection;
  }

  void move(const Direction &moveDir) noexcept;
  void setNewDirection(const Direction &newDir) noexcept;
  void addTail() noexcept;

private:
  Direction mMoveDirection;
  std::list<SnakeHead> mSnake;
  winsize mW{};
};
