#pragma once

#include <bln_audio/types.hpp>

#include <filesystem>
#include <vector>

namespace bln_audio {

using path_t  = std::filesystem::path;
using track_t = std::vector<segment_t>;

auto from_file(const path_t&) -> track_t;

} // namespace bln_audio
