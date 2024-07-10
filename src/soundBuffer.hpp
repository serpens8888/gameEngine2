#ifndef __SOUNDBUFFER_HPP
#define __SOUNDBUFFER_HPP


#include "headers.hpp"
#include "alHelper.hpp"
	
namespace snd {

	struct soundBuffer{
		
		static soundBuffer* get();

		enum formatType{
			Int16,
			Float,
			IMA4,
			MSADPCM
		};

		ALuint addSound(const char* filename);
		bool removeSound(const ALuint& buffer);
		
		soundBuffer();
		~soundBuffer();

		std::vector<ALuint> soundBuffers;


	};

} //snd namespace


#endif
