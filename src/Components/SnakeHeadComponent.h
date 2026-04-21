#pragma once

enum class SnakeDirection { Up, Down, Left, Right };

struct SnakeHeadComponent final {
  SnakeDirection direction = SnakeDirection::Right;
  int length = 1;
};
