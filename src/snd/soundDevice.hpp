#ifndef __SOUNDDEVICE_HPP
#define __SOUNDDEVICE_HPP
#include "headers.hpp"
namespace snd {
struct soundDevice{
	static soundDevice* get();

	soundDevice();
	~soundDevice();

	ALCdevice * device;
	ALCcontext * context;

};

} //namespace snd


#endif
