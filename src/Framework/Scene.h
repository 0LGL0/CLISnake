#pragma once

#include <memory>
#include <vector>

#include <entt/entt.hpp>

#include "World.h"

class Scene final {
public:
  Scene() noexcept = default;
  ~Scene() noexcept = default;

  [[nodiscard]] inline EntityID createNewEntity() noexcept {
    return mWorld.getRegistry().create();
  }
  [[nodiscard]] inline World &getWorld() noexcept { return mWorld; }

  inline void destroyEntity(const EntityID entity) noexcept {
    mWorld.getRegistry().destroy(entity);
  }

  void update(const double dt) noexcept;

private:
  World mWorld;
};

class SceneManager final {
public:
  SceneManager() noexcept = default;
  ~SceneManager() noexcept = default;

  SceneManager(const SceneManager &) = delete;
  SceneManager operator=(const SceneManager &) = delete;
  SceneManager(SceneManager &&) = delete;
  SceneManager operator=(SceneManager &&) = delete;

  [[nodiscard]] Scene *createNewScene() noexcept;
  [[nodiscard]] inline Scene *getScene(const size_t index) noexcept {
    return mScenes[index].get();
  }
  [[nodiscard]] inline Scene *getCurrentScene() noexcept {
    return mCurrentScene;
  }

  void removeScene(const size_t index) noexcept;
  inline void setCurrentScene(Scene *scene) noexcept { mCurrentScene = scene; }

private:
  Scene *mCurrentScene;
  std::vector<std::unique_ptr<Scene>> mScenes;
  std::vector<size_t> mFreedScenes;
};
