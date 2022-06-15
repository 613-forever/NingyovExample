// SPDX-License-Identifier: MIT
// Copyright (c) 2021-2022 613_forever

#include <ningyov/engine.h>
#include <ningyov/drawable.h>

using namespace ningyov;
using namespace ningyov::drawable;

int main() {
  init();
  cuda::init();
  auto cacheDir = COMMON613_STRINGIZE(CACHE_ROOT_DIR)"ExampleSimpleScene/"s,
    clipDir = COMMON613_STRINGIZE(CLIP_DIR)""s;
  Engine::Strategies strategies;
  strategies.push_back(std::make_unique<Engine::SaveFrameByFrame>(cacheDir, "frame_{:05d}"));
  strategies.push_back(std::make_unique<Engine::SaveIntermediateResults>(cacheDir, "frame_{:05d}_L{:02d}"));
  strategies.push_back(std::make_unique<Engine::ChildProcVideo>(cacheDir, "video.mp4"));
  Engine engine(std::move(strategies));
  auto& layers = engine.getLayers();
  // test scene
  auto bg = std::static_pointer_cast<Drawable>(std::make_shared<EntireImage>(clipDir, "background", 1, Vec2i{0, 0}));
  auto dialogBox = std::static_pointer_cast<Drawable>(std::make_shared<Texture>(clipDir, "dialog_box", 1, Vec2i{0, 0}));

  layers.push_back(bg);
  layers.push_back(dialogBox);
  engine.setWaitLength(1_fr);
  engine.renderShot();
  return 0;
}
