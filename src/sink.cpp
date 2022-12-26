#include <bln_audio/sink.hpp>

#include <stdio.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <stdexcept>
#include <thread>


#include <span>
#include <iostream>

namespace bln_audio {

using namespace std::chrono_literals;

namespace {

using Time  = PaStreamCallbackTimeInfo;
using Flags = PaStreamCallbackFlags;

static auto pa_cb(const void*, void* out, const u64 frames, const Time*, const Flags, void* s) -> int
{
    static_cast<sink_t*>(s)->process(static_cast<cfg::sample_t*>(out), frames);
    return paContinue;
}

auto pa_quiet_init() -> PaError
{
    freopen("/dev/null","w", stderr);
    const auto ret = Pa_Initialize();
    freopen("/dev/tty","w", stderr);

    return ret;
}

} // namespace anonym

sink_t::sink_t()
{
    if(pa_quiet_init())
        throw std::runtime_error{"[err] open sink"};

    if(Pa_OpenDefaultStream(&m_stream, 0, cfg::channels, paInt16, cfg::rate, cfg::frames, pa_cb, this))
        throw std::runtime_error{"[err] open stream"};

    Pa_StartStream(m_stream);
}

sink_t::~sink_t()
{
    Pa_StopStream(m_stream);
    Pa_Terminate();
}

auto sink_t::operator<<(segment_t s) -> sink_t&
{
    m_pcm_queue.put(std::move(s));
    return *this;
}

auto sink_t::process(cfg::sample_t* out, const u64) -> bool
{
    const auto segment = m_pcm_queue.get();

    if (!segment)
        std::fill_n(out, cfg::samples, 0);
    else
        std::memcpy(out, (*segment).data(), cfg::bytes);

    return true;
}

} // namespace bln_audio
