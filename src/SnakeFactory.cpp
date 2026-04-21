#include "SnakeFactory.h"
#include "Components/SnakeHeadComponent.h"
#include "Components/SnakeSegmentComponent.h"
#include "Framework/Components/TransformComponent.h"

#include <climits>
#include <entt/entt.hpp>

namespace SnakeFactory {

EntityID spawn(Scene &scene, const int startX, const int startY) noexcept {
  auto &registry = scene.getWorld().getRegistry();

  const EntityID head = scene.createNewEntity();

  registry.emplace<TransformComponent>(
      head, TransformComponent{Vector(startX, startY)});

  registry.emplace<SnakeSegmentComponent>(head, SnakeSegmentComponent{0, true});

  registry.emplace<SnakeHeadComponent>(
      head, SnakeHeadComponent{SnakeDirection::Right, 1});

  return head;
}

void addTail(Scene &scene, const EntityID headEntity) noexcept {
  auto &registry = scene.getWorld().getRegistry();

  entt::entity tailEntity = entt::null;
  int minIndex = INT_MAX;

  auto view = registry.view<SnakeSegmentComponent, TransformComponent>();
  for (auto entity : view) {
    const auto &seg = registry.get<SnakeSegmentComponent>(entity);
    if (seg.segmentIndex < minIndex) {
      minIndex = seg.segmentIndex;
      tailEntity = entity;
    }
  }

  if (tailEntity == entt::null)
    return;

  const auto tailPos = registry.get<TransformComponent>(tailEntity).position;

  for (auto entity : view) {
    auto &seg = registry.get<SnakeSegmentComponent>(entity);
    seg.segmentIndex += 1;
  }

  const EntityID newTail = scene.createNewEntity();

  registry.emplace<TransformComponent>(newTail, TransformComponent{tailPos});

  registry.emplace<SnakeSegmentComponent>(newTail,
                                          SnakeSegmentComponent{0, false});

  auto &headComp = registry.get<SnakeHeadComponent>(headEntity);
  headComp.length += 1;
}

} // namespace SnakeFactory
