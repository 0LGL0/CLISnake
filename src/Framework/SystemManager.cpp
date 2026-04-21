#include "SystemManager.h"

void SystemManager::updateAll(const double dt) const noexcept {
  for (const auto &systems : mSystems) {
    for (auto &system : systems) {
      system->update(mReg, dt);
    }
  }
}
