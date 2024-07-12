#ifndef __SOUNDSOURCE_HPP
#define __SOUNDSOURCE_HPP
	
#include "../headers.hpp"
namespace snd{

struct soundSource{

	soundSource();
	~soundSource();

	void play(const ALuint sound);

	ALuint source;
	ALuint buffer = 0;
	bool loopSound = false;
	float pitch = 1.0f;
	float gain = 1.0f;
	vec3f position = {0,0,0};
	vec3f velocity = {0,0,0};
};
	


} //snd namespace

#endif
