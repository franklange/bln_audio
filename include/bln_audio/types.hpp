#pragma once

#include <bln_audio/config.hpp>
#include <bln_queue/data_queue.hpp>

#include <chrono>

namespace bln_audio {

using u32 = std::uint32_t;
using u64 = std::uint64_t;

using segment_t = std::array<cfg::sample_t, cfg::samples>;
using pcm_queue_t = bln_queue::data_queue<segment_t, cfg::bufsize>;

} // namespace bln_audio
