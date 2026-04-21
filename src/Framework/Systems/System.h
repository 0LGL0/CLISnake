#pragma once

#include <entt/entity/fwd.hpp>

class ISystem {
public:
  virtual void update(entt::registry &registry, const double dt) noexcept = 0;
  virtual ~ISystem() noexcept = default;
};
