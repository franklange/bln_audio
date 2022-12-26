#include <bln_audio/config.hpp>
#include <bln_audio/player.hpp>

#include <thread>

#include <iostream>

namespace bln_audio {

player_t::player_t(pcm_queue_t& q)
    : m_pcm{q}
{}

player_t::~player_t()
{
    stop();

    if (m_thread.joinable())
        m_thread.join();
}

void player_t::play()
{
    if (!m_active)
        return;

    m_sema.release();
}

void player_t::play(track_t t)
{
    m_index  = 0;
    m_active = true;
    m_track  = std::move(t);
    m_thread = std::thread{&player_t::run, this};

    m_sema.release();
}

void player_t::pause()
{
    if (!m_active)
        return;

    m_sema.acquire();
}

void player_t::stop()
{
    m_active = false;
}

void player_t::wait()
{
    if (m_thread.joinable())
        m_thread.join();
}

void player_t::run()
{
    while (m_active && (m_index < m_track.size()))
    {
        m_sema.acquire();
        m_pcm.put(m_track.at(m_index++));
        m_sema.release();

        std::this_thread::sleep_for(cfg::interval);
    }

    m_active = false;
    m_index = 0;
    m_track.clear();
}

} // namespace bln_audio
