// SPDX-License-Identifier: MIT
// Copyright (c) 2021-2022 613_forever

#include <ningyov/engine.h>
#include <ningyov/cuda/cuda_utils.h>
#include <ningyov/text/text_render_utils.h>
#include <ningyov/math/pos_utils.h>
#include <ningyov/drawable.h>
#include <ningyov/drawables/stand.h>

using namespace ningyov;
using namespace ningyov::drawable;
using common613::checked_cast;

const int MUL = 3;

int main() {
  init();
  cuda::init();
  config::FONT_DIRECTORY = COMMON613_STRINGIZE(FONT_DIR);
  font::init();
  auto cacheDir = COMMON613_STRINGIZE(CACHE_ROOT_DIR)"ExmapleMultiShotScene/"s,
      clipDir = COMMON613_STRINGIZE(CLIP_DIR)""s,
      standDir = COMMON613_STRINGIZE(UNPACKED_DIR)""s;
  Engine::Strategies strategies;
//  strategies.push_back(std::make_unique<Engine::SaveIntermediateResults>(cacheDir, "frame_{:05d}_{:02d}"));
//  strategies.push_back(std::make_unique<Engine::SaveFrameByFrame>(cacheDir, "frame_{:05d}"));
  strategies.push_back(std::make_unique<Engine::ChildProcVideo>(cacheDir, "video.mp4"));
  Engine engine(std::move(strategies));
  auto& layers = engine.getLayers();

  Vec2i centerStandOffset{checked_cast<Dim>(config::WIDTH / 2), checked_cast<Dim>(config::HEIGHT)};

  auto bg = std::make_shared<EntireImage>(clipDir, "background", 1, Vec2i{0, 0});
  auto dialogBox = std::make_shared<Texture>(clipDir, "dialog_box", 1, Vec2i{0, 0});
  auto text = std::make_shared<TextLike>("“Hello, World!”", Vec2i{160, 790}, Size::of(360, 1600));

  Frames countDown{{0}};
  auto blinker = std::make_shared<drawable::BlinkSelector>(&countDown, true);
  auto stand = std::make_shared<Stand>(standDir, "01", "0a", "01", MUL, text->duration(), blinker);

  layers.assign({ bg, translate(stand, centerStandOffset), dialogBox, text });
  engine.setWaitLength(0.5_sec);
  engine.renderShot();
  engine.nextShot();

  text = std::make_shared<TextLike>("Hello everyone. My name is Ningyo Kamino.",
                                    Vec2i{160, 760}, Size::of(360, 1600));
  stand->setSpeakingDuration(text->duration());

  layers[3] = text;
  engine.setWaitLength(0.5_sec);
  engine.renderShot();
  engine.nextShot();

  text = std::make_shared<TextLike>("It was the 8th of July, 2021 when my predecessor said the phrase first.",
                                    Vec2i{160, 760}, Size::of(360, 1600));
  stand->setSpeakingDuration(text->duration());

  layers[3] = text;
  engine.setWaitLength(0.5_sec);
  engine.renderShot();
  engine.nextShot();

  text = std::make_shared<TextLike>("She was not ware of what the phrase meant at that time.",
                                    Vec2i{160, 760}, Size::of(360, 1600));
  stand->setSpeakingDuration(text->duration());

  layers[3] = text;
  engine.setWaitLength(0.5_sec);
  engine.renderShot();
  engine.nextShot();

  text = std::make_shared<TextLike>("It is in fact the traditional and typical message programmers use in tests, so...",
                                    Vec2i{160, 760}, Size::of(360, 1600));
  stand->setSpeakingDuration(text->duration());

  layers[3] = text;
  engine.setWaitLength(0.5_sec);
  engine.renderShot();
  engine.nextShot();

  text = std::make_shared<TextLike>("No no no, I bet there is no way that we are just living in a simulated world, "
                                    "in which all what I am saying is displayed in dialog boxes on a screen.",
                                    Vec2i{160, 730}, Size::of(360, 1600));
  stand->setSpeakingDuration(text->duration());

  layers[3] = text;
  engine.setWaitLength(0.5_sec);
  engine.renderShot();

  // global var auto destruction, if arranged after streams, causes crashes when logging.
  ningyov::image::registeredImages.clear();

  return 0;
}
