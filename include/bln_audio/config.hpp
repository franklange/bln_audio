#pragma once

#include <cstdint>

namespace bln_audio::cfg {

using s16 = std::int16_t;
using u32 = std::uint32_t;

using sample_t = s16;

const u32 channels{2};
const u32 rate{44100};

const u32 frames {2048};
const u32 samples{frames  * channels};
const u32 bytes  {samples * sizeof(sample_t)};

} // namespace bln_audio::cfg
