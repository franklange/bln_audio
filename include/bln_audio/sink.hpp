#pragma once

#include <bln_audio/config.hpp>
#include <bln_audio/types.hpp>

#include <portaudio.h>

namespace bln_audio {

class sink_t
{
public:
    sink_t();
    ~sink_t();

    auto process(cfg::sample_t*, u64) -> bool;

    pcm_queue_t  m_pcm_queue;

private:
    PaStream* m_stream;
};

} // namespace bln_audio
