#pragma once
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <fstream>
#include <chrono>
#include <iostream>

namespace audio {

enum Type { PLAY,
            LOOP };

// Loop control
inline std::atomic<bool> loopFlag(false);
inline std::thread loopThread;

// ----------------------
// Forward declarations
inline bool init();
inline void shutdown();
inline void stopAll();
inline void play(const std::string &path, Type type = PLAY);

// ----------------------
// Platform-specific includes & helpers
#ifdef _WIN32
#include <windows.h>
inline void playWin(const std::string &path, Type type) {
    DWORD flags = SND_FILENAME | SND_ASYNC;
    if (type == LOOP)
        flags |= SND_LOOP;
    PlaySoundA(path.c_str(), NULL, flags);
}
#elif defined(__APPLE__)
#include <AudioToolbox/AudioToolbox.h>
inline void playMac(const std::string &path, Type type) {
    loopFlag = (type == LOOP);
    if (loopThread.joinable())
        loopThread.join();

    loopThread = std::thread([path]() {
        do {
            CFStringRef cfPath = CFStringCreateWithCString(NULL, path.c_str(), kCFStringEncodingUTF8);
            CFURLRef url = CFURLCreateWithFileSystemPath(NULL, cfPath, kCFURLPOSIXPathStyle, false);
            SystemSoundID soundID;
            AudioServicesCreateSystemSoundID(url, &soundID);
            AudioServicesPlaySystemSound(soundID);
            CFRelease(cfPath);
            CFRelease(url);

            std::this_thread::sleep_for(std::chrono::seconds(2)); // naive duration
        } while (loopFlag);
    });
}
#elif defined(__linux__)
#include <alsa/asoundlib.h>
#include <pulse/simple.h>
#include <pulse/error.h>

inline void playLinux(const std::string &path, Type type) {
    loopFlag = (type == LOOP);
    if (loopThread.joinable())
        loopThread.join();

    loopThread = std::thread([path]() {
        do {
            // Try PulseAudio first
            pa_sample_spec ss{};
            ss.format = PA_SAMPLE_S16LE;
            ss.channels = 2;
            ss.rate = 44100;
            int error;
            pa_simple *pa = pa_simple_new(NULL, "GameEngine", PA_STREAM_PLAYBACK,
                                          NULL, "Playback", &ss, NULL, NULL, &error);
            if (pa) {
                // Read WAV data (skip header)
                std::ifstream file(path, std::ios::binary);
                if (!file)
                    break;
                file.seekg(44);
                std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
                                         std::istreambuf_iterator<char>());
                pa_simple_write(pa, buffer.data(), buffer.size(), &error);
                pa_simple_drain(pa, &error);
                pa_simple_free(pa);
            } else {
                // Fallback to ALSA
                snd_pcm_t *pcm;
                if (snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
                    break;
                snd_pcm_set_params(pcm, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED,
                                   2, 44100, 1, 500000);
                std::ifstream file(path, std::ios::binary);
                if (!file) {
                    snd_pcm_close(pcm);
                    break;
                }
                file.seekg(44);
                std::vector<char> buffer(4096);
                while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
                    snd_pcm_writei(pcm, buffer.data(), file.gcount() / 4);
                }
                snd_pcm_close(pcm);
            }
        } while (loopFlag);
    });
}
#endif

// ----------------------
// API implementation

inline bool init() { return true; }

inline void shutdown() { stopAll(); }

inline void stopAll() {
    loopFlag = false;
    if (loopThread.joinable())
        loopThread.join();
#ifdef _WIN32
    PlaySoundA(NULL, 0, 0);
#endif
}

inline void play(const std::string &path, Type type) {
#ifdef _WIN32
    playWin(path, type);
#elif defined(__APPLE__)
    playMac(path, type);
#elif defined(__linux__)
    playLinux(path, type);
#else
    static_assert(false, "Unsupported platform");
#endif
}

} // namespace audio