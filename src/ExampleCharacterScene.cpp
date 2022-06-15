// SPDX-License-Identifier: MIT
// Copyright (c) 2021-2022 613_forever

#include <ningyov/engine.h>
#include <ningyov/cuda/cuda_utils.h>
#include <ningyov/math/pos_utils.h>
#include <ningyov/drawable.h>
#include <ningyov/abstraction/position.h>
#include <ningyov/abstraction/character_to_draw.h>
#include <ningyov/text/text_render_utils.h>

using namespace ningyov;
using namespace ningyov::drawable;
using namespace ningyov::abstraction;
using common613::checked_cast;

int main() {
  init();
  cuda::init();
  config::FONT_DIRECTORY = COMMON613_STRINGIZE(FONT_DIR);
  font::init();

  auto cacheDir = COMMON613_STRINGIZE(CACHE_ROOT_DIR)"ExampleCharacterScene/"s,
      clipDir = COMMON613_STRINGIZE(CLIP_DIR)""s,
      standDir = COMMON613_STRINGIZE(UNPACKED_DIR)""s;

  auto ningyo = std::make_shared<CharacterToDraw>(clipDir, "dialog_box",
                                                  standDir, "01",
                                                  enumToPosition(Position::MIDDLE));

  auto lines = std::make_shared<TextLike>("Hello, world!", Vec2i::of(160, 790), Size::of(360, 1600));
  ningyo->speaksAndChangesExprInNextShot(lines, "0a", "01", false);

  Engine::Strategies strategies;
  strategies.push_back(std::make_unique<Engine::ChildProcVideo>(cacheDir, "out.mp4"));
  Engine engine(std::move(strategies));
  auto& layers = engine.getLayers();

  auto bg = std::static_pointer_cast<Drawable>(std::make_shared<EntireImage>(clipDir, "background", 1, Vec2i{0, 0}));

  layers.push_back(bg);
  layers.push_back(ningyo);
  layers.push_back(ningyo->getDialog());

  engine.setTotalLength(5_sec);
  engine.renderShot();

  image::registeredImages.clear();
  return 0;
}
