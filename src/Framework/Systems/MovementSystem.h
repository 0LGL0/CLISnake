#pragma once
#include "System.h"
#include <entt/entity/fwd.hpp>

class MovementSystem final : public ISystem {
public:
  void update(entt::registry &registry, const double dt) noexcept override;
};
