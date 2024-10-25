#ifndef __SOUNDSOURCE_HPP
#define __SOUNDSOURCE_HPP
	
#include "headers.hpp"
namespace snd{

struct speakerCreationData{

	bool loopSound;
	float gain;
	float pitch;
	vec3f position;
	vec3f velocity;
};

struct soundSource{

//	soundSource();
	~soundSource();

	void play(const ALuint sound);
	void create(speakerCreationData creationData);

	ALuint source;
	ALuint buffer = 0;
	speakerCreationData creationData;
};
	
} //snd namespace

#endif
