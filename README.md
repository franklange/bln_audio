# bln_audio
Simple audio playback engine and utilities.

### Dependencies
* portaudio
* libsndfile
* bln_queue

### Example
```c++
#include <bln_audio/all.hpp>
#include <thread>

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
```

### Build & Run example
```bash
git clone --recursive https://github.com/franklange/bln_audio.git
cd bln_audio
mkdir build
cd build
cmake -DBLN_AUDIO_EXAMPLES=ON ..
cmake --build . -j
(cd bin && ./bln_audio_example)
```

### Config
For now the audio config is done via code and set up for basic music playback.\
Please adjust for your use-case and recompile.
```c++
using sample_t = s16;

const u32 channels{2};
const u32 rate{44100};

const u32 frames {2048};
const u32 samples{frames  * channels};
const u32 bytes  {samples * sizeof(sample_t)};

const u32 bufsize{16};
const ms interval{45};
```
