// SPDX-License-Identifier: MIT
// Copyright (c) 2021-2022 613_forever

#include <ningyov/engine.h>
#include <ningyov/cuda/cuda_utils.h>
#include <ningyov/text/text_render_utils.h>
#include <ningyov/math/pos_utils.h>
#include <ningyov/drawable.h>

using namespace ningyov;
using namespace ningyov::config;
using namespace ningyov::drawable;
using common613::checked_cast;

int main() {
  init();
  cuda::init();
  config::FONT_DIRECTORY = COMMON613_STRINGIZE(FONT_DIR);
  font::init();

  auto cacheDir = COMMON613_STRINGIZE(CACHE_ROOT_DIR)"ExampleDialogTextScene/"s,
      clipDir = COMMON613_STRINGIZE(CLIP_DIR)""s,
      standDir = COMMON613_STRINGIZE(UNPACKED_DIR)""s;
  Engine::Strategies strategies;
  strategies.emplace_back(new Engine::SaveFrameByFrame(cacheDir, "frame_{:05d}"));
  Engine engine(std::move(strategies));
  auto& layers = engine.getLayers();
  Vec2i centerStandOffset{checked_cast<Dim>(config::WIDTH / 2), checked_cast<Dim>(config::HEIGHT)};
  auto bg = std::static_pointer_cast<Drawable>(
      std::make_shared<EntireImage>(clipDir, "background", 1, Vec2i{0, 0}));
  auto dialogBox = std::static_pointer_cast<Drawable>(
      std::make_shared<Texture>(clipDir, "dialog_box", 1, Vec2i{0, 0}));
  auto text = std::static_pointer_cast<Drawable>(
      std::make_shared<TextLike>("Hello, World!", Vec2i{160, 790}, Size::of(360, 1600), false, 0)
      );
  auto stand = std::static_pointer_cast<Drawable>(
      std::make_shared<Stand>(standDir, "01", "0a", "01", 4, text->duration()));

  layers.push_back(bg);
//  layers.push_back(std::make_shared<Translated>(stand, centerStandOffset));
  layers.push_back(translate(stand, centerStandOffset));
  layers.push_back(dialogBox);
  layers.push_back(text);
  engine.setWaitLength(0.3_sec);
  engine.renderShot();

  ningyov::image::registeredImages.clear();
  return 0;
}
