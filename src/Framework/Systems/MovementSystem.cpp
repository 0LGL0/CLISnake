#include "MovementSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/VelocityComponent.h"
#include <entt/entt.hpp>

void MovementSystem::update(entt::registry &registry,
                            const double dt) noexcept {
  const auto view = registry.view<TransformComponent, VelocityComponent>();
  for (auto &entity : view) {
    auto &trans = registry.get<TransformComponent>(entity);
    auto &vel = registry.get<VelocityComponent>(entity);

    trans.position.x *= vel.velocity.x * dt;
    trans.position.y *= vel.velocity.y * dt;
  }
}
