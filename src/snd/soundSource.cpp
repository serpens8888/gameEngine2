#include "soundSource.hpp"



namespace snd{


void soundSource::create(speakerCreationData creationData){
            alGenSources(1, &source);
            alSourcef(source, AL_PITCH, creationData.pitch);
            alSourcef(source, AL_GAIN, creationData.gain);
            alSource3f(source, AL_POSITION, creationData.position.x, creationData.position.y, creationData.position.z);
            alSource3f(source, AL_VELOCITY, creationData.velocity.x, creationData.velocity.y, creationData.velocity.z);
            alSourcei(source, AL_LOOPING, creationData.loopSound);
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
