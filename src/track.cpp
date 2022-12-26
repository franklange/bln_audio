#include <bln_audio/track.hpp>

#include <sndfile.h>

namespace bln_audio {

auto from_file(const path_t& p) -> track_t
{
    SF_INFO info;
    auto* file = sf_open(p.c_str(), SFM_READ, &info);

    if (!file)
        throw std::runtime_error{"[track] couldn't open file"};

    track_t res;
    res.resize((info.frames / cfg::frames) + 1);

    for (auto& seg : res)
        sf_readf_short(file, seg.data(), cfg::frames);

    sf_close(file);

    return res;
}

} // namespace bln_audio
