#ifndef __SOUNDGENERATOR_HPP
#define __SOUNDGENERATOR_HPP

#include "../headers.hpp"

namespace snd{
	namespace procedural{

		enum waveformType{
			sine,
			square,
			triangle,
			sawtooth,
			pulse,
		};

		struct waveform{
			waveformType type;
			float length;
			float frequency;
			float amplitude;
			float offset;
			std::optional<float> dutyCylce;
		};

		struct envelope{
			float attack;
			float decay;
			float sustain;
			float release;
		};

		struct modulation{
			std::vector<float> modFrequencies;
			std::vector<float> modAmplitudes;
		};

		enum filterType{

		};

		struct filter{
			filterType type;
			float cutoff;
		};
	
		enum effects{
			delay,
			reverb,
		};

		enum dataType{
			Float,
			I16
		};

		
		struct soundInfo{

		float duration;
		float sampleRate;
		float frequency;
		float amplitude;
		waveformType waveform;
		dataType type;
		};

		struct soundGenerator{
			ALuint makeSound(soundInfo& info);

			soundGenerator();
			~soundGenerator();
		};

	} //procedural namespace
} //snd namespace

#endif
