#include "SnakeMovementSystem.h"
#include "Components/SnakeHeadComponent.h"
#include "Components/SnakeSegmentComponent.h"
#include "Framework/Components/TransformComponent.h"

#include <algorithm>
#include <entt/entt.hpp>
#include <vector>

void SnakeMovementSystem::update(entt::registry &registry,
                                 const double dt) noexcept {
  struct SegInfo {
    entt::entity entity;
    int index;
  };

  std::vector<SegInfo> segments;
  segments.reserve(64);

  auto view = registry.view<SnakeSegmentComponent, TransformComponent>();
  for (auto entity : view) {
    const auto &seg = registry.get<SnakeSegmentComponent>(entity);
    segments.push_back({entity, seg.segmentIndex});
  }

  if (segments.empty())
    return;

  std::sort(
      segments.begin(), segments.end(),
      [](const SegInfo &a, const SegInfo &b) { return a.index < b.index; });

  entt::entity headEntity = entt::null;
  for (const auto &s : segments) {
    if (registry.get<SnakeSegmentComponent>(s.entity).isHead) {
      headEntity = s.entity;
      break;
    }
  }
  if (headEntity == entt::null)
    return;

  const auto &headComp = registry.get<SnakeHeadComponent>(headEntity);

  for (size_t i = 0; i + 1 < segments.size(); ++i) {
    auto &cur = registry.get<TransformComponent>(segments[i].entity);
    const auto &next = registry.get<TransformComponent>(segments[i + 1].entity);
    cur.position = next.position;
  }

  auto &headTrans = registry.get<TransformComponent>(headEntity);
  switch (headComp.direction) {
    using enum SnakeDirection;
  case Up:
    headTrans.position.y -= 1;
    break;
  case Down:
    headTrans.position.y += 1;
    break;
  case Left:
    headTrans.position.x -= 1;
    break;
  case Right:
    headTrans.position.x += 1;
    break;
  }
}
