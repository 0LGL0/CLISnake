#include "Snake.h"

Snake::Snake(const winsize &w) noexcept : mW(w) {
  mSnake.resize(1, SnakeHead{0, 0});
  mMoveDirection = Direction::Right;
}

void Snake::move(const Direction &moveDir) noexcept {
  mMoveDirection = moveDir;
  const SnakeHead currHead = mSnake.back();
  SnakeHead newHead = SnakeHead{currHead.x, currHead.y};
  switch (moveDir) {
    using enum Direction;
  case Up:
    newHead.y -= 1;
    break;
  case Down:
    newHead.y += 1;
    break;
  case Left:
    newHead.x -= 1;
    break;
  case Right:
    newHead.x += 1;
    break;
  }

  mSnake.pop_front();
  mSnake.push_back(newHead);
}

void Snake::addTail() noexcept {
  const SnakeHead currTail = mSnake.front();
  SnakeHead newTail{currTail.x, currTail.y};
  switch (mMoveDirection) {
    using enum Direction;
  case Up:
    newTail.y += 1;
    break;
  case Down:
    newTail.y -= 1;
  case Left:
    newTail.x += 1;
  case Right:
    newTail.x -= 1;
    break;
  }
  mSnake.push_front(newTail);
}
