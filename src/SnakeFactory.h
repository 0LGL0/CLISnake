#pragma once

#include "Framework/Scene.h"
#include "Framework/World.h"

namespace SnakeFactory {

[[nodiscard]] EntityID spawn(Scene &scene, int startX, int startY) noexcept;

void addTail(Scene &scene, EntityID headEntity) noexcept;

} // namespace SnakeFactory
