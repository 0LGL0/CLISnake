#pragma once

#include "Framework/Systems/System.h"
#include <entt/entity/fwd.hpp>

class SnakeMovementSystem final : public ISystem {
public:
  void update(entt::registry &registry, const double dt) noexcept override;
};
