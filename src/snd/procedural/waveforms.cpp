#include "waveforms.hpp"


namespace snd{

    namespace procedural{

    std::vector<i16> generateSineWave(float frequency, float duration) {
        int numSamples = static_cast<int>(duration * SAMPLE_RATE);
        std::vector<i16> samples(numSamples);

        for (int i = 0; i < numSamples; ++i) {
            samples[i] = static_cast<i16>(32767 * std::sin(2.0 * std::numbers::pi * frequency * i / SAMPLE_RATE));
        }

        return samples;
    }


    };





} //snd namespace
