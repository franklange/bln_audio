#pragma once

#include <chrono>
#include <cstdint>

namespace bln_audio::cfg {

using s16 = std::int16_t;
using u32 = std::uint32_t;
using ms  = std::chrono::milliseconds;

using sample_t = s16;

const u32 channels{2};
const u32 rate{44100};

const u32 frames {2048};
const u32 samples{frames  * channels};
const u32 bytes  {samples * sizeof(sample_t)};

const u32 bufsize{16};
const ms interval{45};

} // namespace bln_audio::cfg
