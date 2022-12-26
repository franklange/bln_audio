#include <bln_audio/all.hpp>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

auto main() -> int
{
    bln_audio::sink_t sink;
    bln_audio::player_t player{sink.m_pcm_queue};

    auto track = bln_audio::from_file("wav/piano.wav");

    // manual push
    for (const auto& segment : track)
    {
        sink << segment;
        std::this_thread::sleep_for(bln_audio::cfg::interval);
    }

    // async player with pause/resume
    player.play(std::move(track));
    std::this_thread::sleep_for(2s);

    player.pause();
    std::this_thread::sleep_for(2s);

    player.play();
    player.wait();

    return 0;
}
