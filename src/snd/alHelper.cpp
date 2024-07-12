#include "alHelper.hpp"


const char *formatName(ALenum format){

switch(format){

            case AL_FORMAT_MONO8: return "Mono, U8";

            case AL_FORMAT_MONO16: return "Mono, S16";

            case AL_FORMAT_MONO_FLOAT32: return "Mono, Float32";

            case AL_FORMAT_MONO_MULAW: return "Mono, muLaw";

            case AL_FORMAT_MONO_ALAW_EXT: return "Mono, aLaw";

            case AL_FORMAT_MONO_IMA4: return "Mono, IMA4 ADPCM";

            case AL_FORMAT_MONO_MSADPCM_SOFT: return "Mono, MS ADPCM";

            case AL_FORMAT_STEREO8: return "Stereo, U8";

            case AL_FORMAT_STEREO16: return "Stereo, S16";

            case AL_FORMAT_STEREO_FLOAT32: return "Stereo, Float32";

            case AL_FORMAT_STEREO_MULAW: return "Stereo, muLaw";

            case AL_FORMAT_STEREO_ALAW_EXT: return "Stereo, aLaw";

            case AL_FORMAT_STEREO_IMA4: return "Stereo, IMA4 ADPCM";

            case AL_FORMAT_STEREO_MSADPCM_SOFT: return "Stereo, MS ADPCM";

            case AL_FORMAT_QUAD8: return "Quadraphonic, U8";

            case AL_FORMAT_QUAD16: return "Quadraphonic, S16";

            case AL_FORMAT_QUAD32: return "Quadraphonic, Float32";

            case AL_FORMAT_QUAD_MULAW: return "Quadraphonic, muLaw";

            case AL_FORMAT_51CHN8: return "5.1 Surround, U8";

            case AL_FORMAT_51CHN16: return "5.1 Surround, S16";

            case AL_FORMAT_51CHN32: return "5.1 Surround, Float32";

            case AL_FORMAT_51CHN_MULAW: return "5.1 Surround, muLaw";

            case AL_FORMAT_61CHN8: return "6.1 Surround, U8";

            case AL_FORMAT_61CHN16: return "6.1 Surround, S16";

            case AL_FORMAT_61CHN32: return "6.1 Surround, Float32";

            case AL_FORMAT_61CHN_MULAW: return "6.1 Surround, muLaw";

            case AL_FORMAT_71CHN8: return "7.1 Surround, U8";

            case AL_FORMAT_71CHN16: return "7.1 Surround, S16";

            case AL_FORMAT_71CHN32: return "7.1 Surround, Float32";

            case AL_FORMAT_71CHN_MULAW: return "7.1 Surround, muLaw";

            case AL_FORMAT_BFORMAT2D_8: return "B-Format 2D, U8";

            case AL_FORMAT_BFORMAT2D_16: return "B-Format 2D, S16";

            case AL_FORMAT_BFORMAT2D_FLOAT32: return "B-Format 2D, Float32";

            case AL_FORMAT_BFORMAT2D_MULAW: return "B-Format 2D, muLaw";

            case AL_FORMAT_BFORMAT3D_8: return "B-Format 3D, U8";

            case AL_FORMAT_BFORMAT3D_16: return "B-Format 3D, S16";

            case AL_FORMAT_BFORMAT3D_FLOAT32: return "B-Format 3D, Float32";

            case AL_FORMAT_BFORMAT3D_MULAW: return "B-Format 3D, muLaw";

            case AL_FORMAT_UHJ2CHN8_SOFT: return "UHJ 2-channel, U8";

            case AL_FORMAT_UHJ2CHN16_SOFT: return "UHJ 2-channel, S16";

            case AL_FORMAT_UHJ2CHN_FLOAT32_SOFT: return "UHJ 2-channel, Float32";

            case AL_FORMAT_UHJ3CHN8_SOFT: return "UHJ 3-channel, U8";

            case AL_FORMAT_UHJ3CHN16_SOFT: return "UHJ 3-channel, S16";

            case AL_FORMAT_UHJ3CHN_FLOAT32_SOFT: return "UHJ 3-channel, Float32";

            case AL_FORMAT_UHJ4CHN8_SOFT: return "UHJ 4-channel, U8";

            case AL_FORMAT_UHJ4CHN16_SOFT: return "UHJ 4-channel, S16";

            case AL_FORMAT_UHJ4CHN_FLOAT32_SOFT: return "UHJ 4-channel, Float32";

            }

        return "Unknown Format";

}
