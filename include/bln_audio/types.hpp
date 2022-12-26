#pragma once

#include <bln_audio/config.hpp>
#include <bln_queue/data_queue.hpp>

namespace bln_audio {

using u64 = std::uint64_t;

using segment_t = std::array<cfg::sample_t, cfg::samples>;
using pcm_queue_t = bln_queue::data_queue<segment_t, 1024>;

} // namespace bln_audio
