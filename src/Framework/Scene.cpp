#include "Scene.h"

#include <memory>

[[nodiscard]] Scene *SceneManager::createNewScene() noexcept {
  if (mFreedScenes.empty()) {
    mScenes.push_back(std::make_unique<Scene>());
    return mScenes.back().get();
  }

  const size_t freedSceneIndex = mFreedScenes.back();
  mFreedScenes.pop_back();
  mScenes[freedSceneIndex] = std::make_unique<Scene>();
  return mScenes[freedSceneIndex].get();
}

void SceneManager::removeScene(const size_t index) noexcept {
  if (mScenes[index].get() == mCurrentScene)
    mCurrentScene = nullptr;
  mScenes[index] = std::make_unique<Scene>();
  mFreedScenes.push_back(index);
}

void Scene::update(const double dt) noexcept { mWorld.update(dt); }
