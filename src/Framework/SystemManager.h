#pragma once
#include "Systems/System.h"
#include <entt/entity/fwd.hpp>
#include <vector>

enum class SystemPriority { Physics, Count };

class SystemManager final {
public:
  explicit SystemManager(entt::registry &registry) noexcept : mReg(registry) {
    mSystems.reserve(static_cast<size_t>(SystemPriority::Count));
    mSystems.resize(static_cast<size_t>(SystemPriority::Count));
  }
  ~SystemManager() noexcept = default;

  template <typename T>
  inline void registryNewSystem(const SystemPriority prioriry) noexcept {
    if (prioriry != SystemPriority::Count)
      mSystems[static_cast<size_t>(prioriry)].push_back(std::make_unique<T>());
  }

  void updateAll(const double dt) const noexcept;

private:
  std::vector<std::vector<std::unique_ptr<ISystem>>> mSystems;
  entt::registry &mReg;
};
