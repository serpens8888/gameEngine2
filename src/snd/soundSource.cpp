#include "soundSource.hpp"



namespace snd{


soundSource::soundSource(){
            alGenSources(1, &source);
            alSourcef(source, AL_PITCH, pitch);
            alSourcef(source, AL_GAIN, gain);
            alSource3f(source, AL_POSITION, position.x, position.y, position.z);
            alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
            alSourcei(source, AL_LOOPING, loopSound);
            alSourcef(source, AL_BUFFER, buffer);
}

soundSource::~soundSource(){
            alDeleteSources(1, &source);
}

void soundSource::play(const ALuint sound){
            if(sound != buffer){
                        buffer = sound;
                        alSourcei(source, AL_BUFFER, (ALint)buffer);
            }
            alSourcePlay(source);

}


} //snd namespace
