#include "soundGen.hpp"

namespace snd {

    generateSound::generateSound(std::vector<i16> soundData) : soundData{soundData} {

    alGenBuffers(1, &buffer);

    alBufferData(buffer, AL_FORMAT_MONO16, soundData.data(), soundData.size() * sizeof(i16), snd::SAMPLE_RATE);

    std::cout << "generated sound" << std::endl;


    }


    generateSound::~generateSound(){

        alDeleteBuffers(1, &buffer);


    }





} // namespace snd
