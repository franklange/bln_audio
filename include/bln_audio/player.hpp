#pragma once

#include <bln_audio/track.hpp>
#include <bln_audio/types.hpp>

#include <atomic>
#include <semaphore>
#include <thread>

namespace bln_audio {

class player_t
{
    using flag_t = std::atomic_bool;
    using semaphore_t = std::binary_semaphore;

public:
    player_t(pcm_queue_t&);
    ~player_t();

    void play();
    void play(track_t);

    void pause();
    void stop();

    void wait();

private:
    void run();

    pcm_queue_t& m_pcm;

    u32  m_index{0};
    track_t m_track;

    flag_t m_active{false};
    semaphore_t m_sema{0};
    std::thread m_thread;
};

} // namespace bln_audio
