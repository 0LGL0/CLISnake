#pragma once

#include "Scene.h"

class EngineManager final {
public:
  EngineManager(const EngineManager &) = delete;
  EngineManager &operator=(const EngineManager &) = delete;
  EngineManager(EngineManager &&) = delete;
  EngineManager &operator=(EngineManager &&) = delete;

  [[nodiscard]] inline static EngineManager &getInstance() noexcept {
    static EngineManager instance;
    return instance;
  }

  [[nodiscard]] inline SceneManager &getSceneManager() noexcept {
    return mSceneManager;
  }

private:
  EngineManager() noexcept = default;
  ~EngineManager() noexcept = default;

  SceneManager mSceneManager;
};
