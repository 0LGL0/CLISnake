#pragma once

#include "SystemManager.h"

#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>

using EntityID = entt::entity;

class World final {
public:
  World() noexcept : mSystemManager(mReg) {}
  ~World() noexcept = default;

  [[nodiscard]] inline entt::registry &getRegistry() noexcept { return mReg; }
  [[nodiscard]] inline SystemManager &getSystemManager() noexcept {
    return mSystemManager;
  }

  template <typename T, typename... Args>
  inline void addComponent(const EntityID entityID, Args... args) noexcept {
    mReg.emplace<T>(entityID, std::forward(args)...);
  }

  void update(const double dt) noexcept { mSystemManager.updateAll(dt); }

private:
  entt::registry mReg;
  SystemManager mSystemManager;
};
