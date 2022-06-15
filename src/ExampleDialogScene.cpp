// SPDX-License-Identifier: MIT
// Copyright (c) 2021-2022 613_forever

#include <ningyov/engine.h>
#include <ningyov/cuda/cuda_utils.h>
#include <ningyov/math/pos_utils.h>
#include <ningyov/drawable.h>

using namespace ningyov;
using namespace ningyov::drawable;

int main() {
  init();
  cuda::init();
  auto cacheDir = COMMON613_STRINGIZE(CACHE_ROOT_DIR)"ExampleDialogScene/"s,
      clipDir = COMMON613_STRINGIZE(CLIP_DIR)""s,
      standDir = COMMON613_STRINGIZE(UNPACKED_DIR)""s;
  Engine::Strategies strategies;
  strategies.push_back(std::make_unique<Engine::SaveIntermediateResults>(cacheDir, "frame_{:05d}_L{:02d}"));
  Engine engine(std::move(strategies));
  auto& layers = engine.getLayers();

  Vec2i centerStandOffset{static_cast<short>(config::WIDTH / 2), static_cast<short>(config::HEIGHT)};
  auto bg = std::static_pointer_cast<Drawable>(
      std::make_shared<EntireImage>(clipDir, "background", 1, Vec2i{0, 0}));
  auto dialogBox = std::static_pointer_cast<Drawable>(
      std::make_shared<Texture>(clipDir, "dialog_box", 1, Vec2i{0, 0}));
  auto stand = std::static_pointer_cast<Drawable>(
      std::make_shared<Stand>(standDir, "01", "0a", "01", 3, 0.5_sec));

  layers.push_back(bg);
//  layers.push_back(std::make_shared<Translated>(stand, centerStandOffset));
  layers.push_back(translate(stand, centerStandOffset));
  layers.push_back(dialogBox);
  engine.setWaitLength(0.1_sec);
  engine.renderShot();

  image::registeredImages.clear();
  return 0;
}
