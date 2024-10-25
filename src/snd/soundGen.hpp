#ifndef __SOUNDGEN_HPP
#define __SOUNDGEN_HPP

#include "headers.hpp"
#include "constants.hpp"


namespace snd{


	struct generateSound{

		u32 buffer;
		std::vector<i16> soundData;


		generateSound(std::vector<i16> soundData);


	    static std::vector<i16> generateSineWavePCM16(float frequency, float duration);

		~generateSound();




	};




} //snd namespace


#endif
