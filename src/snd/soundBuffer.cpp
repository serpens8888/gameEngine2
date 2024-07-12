#include "soundBuffer.hpp"


namespace snd {

   soundBuffer* soundBuffer::get(){
        static soundBuffer* buffer = new soundBuffer();
        return buffer;
    }

    ALuint soundBuffer::addSound(const char* filename){
      enum formatType sample_format = Int16;
      ALint byteBlockAlign = 0;
      ALint sampleBlockAlign = 0;
      sf_count_t frames;
      ALsizei bytes;
      SNDFILE* sndfile;
      SF_INFO sfinfo;
      ALenum err;
      ALenum format;
      ALuint buffer;
//      std::vector<std::byte*> membuf;
      void* membuf;


      sndfile = sf_open(filename, SFM_READ, &sfinfo);
      if(!sndfile){
         std::cerr << "could not open audio file:" << filename << "\n" << sf_strerror(sndfile) << "\n";
      }

      if(sfinfo.frames<1){
         std::cerr << "bad sample count in:" << filename << "\n" << sfinfo.frames << "\n";
      }
      
      switch((sfinfo.format&SF_FORMAT_SUBMASK)){ // uses fall through to set correct sample format for different file formats, the ones not listed here are all int16. for example, alac_16 is 16 bits and can be Int16
      // the rest use other formats because theu hold more data or its a different type, float is 32 bits and can represent 20 24 and 32, so int32 isnt used for alac_32 because float is more convenient ad works all the same?
      // unsure about the accuracy of this comment
         case SF_FORMAT_PCM_24:
         case SF_FORMAT_PCM_32:
         case SF_FORMAT_FLOAT:
         case SF_FORMAT_DOUBLE:
         case SF_FORMAT_VORBIS:
         case SF_FORMAT_OPUS:
         case SF_FORMAT_ALAC_20:
         case SF_FORMAT_ALAC_24:
         case SF_FORMAT_ALAC_32:
         case SF_FORMAT_MPEG_LAYER_I:
         case SF_FORMAT_MPEG_LAYER_II:
         case SF_FORMAT_MPEG_LAYER_III:
            if(alIsExtensionPresent("AL_EXT_FLOAT32"))
               sample_format = Float;
            break;
         case SF_FORMAT_IMA_ADPCM:
            if(sfinfo.channels <= 2 && (sfinfo.format&SF_FORMAT_TYPEMASK) == SF_FORMAT_WAV && alIsExtensionPresent("AL_EXT_IMA4") && alIsExtensionPresent("AL_SOFT_block_alignment"))
               sample_format = IMA4;
            break;
         case SF_FORMAT_MS_ADPCM:
            if(sfinfo.channels <= 2 && (sfinfo.format&SF_FORMAT_TYPEMASK) == SF_FORMAT_WAV && alIsExtensionPresent("AL_EXT_IMA4") && alIsExtensionPresent("AL_SOFT_block_alignment"))
               sample_format = MSADPCM;
            break;
      }

      if(sample_format == IMA4 || sample_format == MSADPCM){
         SF_CHUNK_INFO inf = { "fmt ", 4, 0, NULL }; // magic audio stuff - finds files fmt chunk  which has structure for audio format
         SF_CHUNK_ITERATOR *iter = sf_get_chunk_iterator(sndfile, &inf);
         if(!iter || sf_get_chunk_size(iter, &inf) != SF_ERR_NO_ERROR || inf.datalen < 14) //if there is an issue use 16 bit format and sndfile will do the conversion
            sample_format = Int16;
         else{
            ALubyte *fmtbuf = static_cast<u8*>(calloc(inf.datalen, 1));
            inf.data = fmtbuf;
            if(sf_get_chunk_data(iter, &inf) != SF_ERR_NO_ERROR)
               sample_format = Int16;
            else{
               // read block alignment go from bytes to samples per block and then converting back and checking validity
               // magic numbers straight from the example code
               byteBlockAlign = fmtbuf[12] | (fmtbuf[13]<<8);
               if(sample_format == IMA4){
                  sampleBlockAlign = (byteBlockAlign/sfinfo.channels - 4)*2+1;   // /4*8+1;
                  if(sampleBlockAlign < 1 || ((sampleBlockAlign-1)/2+4)*sfinfo.channels != byteBlockAlign)
                     sample_format = Int16;
               }
               else{
                  sampleBlockAlign = (byteBlockAlign/sfinfo.channels - 7)*2+2;
                  if(sampleBlockAlign < 2 || ((sampleBlockAlign-2)/2+7)*sfinfo.channels != byteBlockAlign)
                     sample_format = Int16;
               }


            }
            free(fmtbuf);
         }
            
      }


      if(sample_format == Int16){
         sampleBlockAlign = 1;
         byteBlockAlign = sfinfo.channels*2;
      }
      else if(sample_format == Float){
         sampleBlockAlign = 1;
         byteBlockAlign = sfinfo.channels*4;
      }

      format = AL_NONE;
      switch(sfinfo.channels){
         case 1:
            switch(sample_format){
               case Int16: format = AL_FORMAT_MONO16; break;
               case Float: format = AL_FORMAT_MONO_FLOAT32; break;
               case IMA4: format = AL_FORMAT_MONO_IMA4; break;
               case MSADPCM: format = AL_FORMAT_MONO_MSADPCM_SOFT; break;
            }
         break;
               
         case 2:
            switch(sample_format){
               case Int16: format = AL_FORMAT_STEREO16; break;
               case Float: format = AL_FORMAT_STEREO_FLOAT32; break;
               case IMA4: format = AL_FORMAT_STEREO_IMA4; break;
               case MSADPCM: format = AL_FORMAT_STEREO_MSADPCM_SOFT; break;
            }
         break;

         case 3:
            if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT){
               switch(sample_format){
                  case Int16: format = AL_FORMAT_BFORMAT2D_16; break;
                  case Float: format = AL_FORMAT_BFORMAT2D_FLOAT32; break;
                  default: break;
               }
            }
         break;
         
         case 4:
            if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT){
               switch(sample_format){
                  case Int16: format = AL_FORMAT_BFORMAT3D_16; break;
                  case Float: format = AL_FORMAT_BFORMAT3D_FLOAT32; break;
                  default: break;
               }
            }
         break;
      }

      if(!format){
         std::cerr << "unsupported channel count: " << sfinfo.channels << "\n";
         sf_close(sndfile);
         return 0;
      }
      
      if(sfinfo.frames/sampleBlockAlign > (sf_count_t)(INT_MAX/byteBlockAlign)){
         std::cerr << "too many samples in: " << filename << sfinfo.frames << "\n";
         sf_close(sndfile);
         return 0;
      }
      
      //decode the audio file to the buffer
      membuf = malloc((size)(sfinfo.frames / sampleBlockAlign *byteBlockAlign));
      
      if(sample_format == Int16)
         frames = sf_readf_short(sndfile, reinterpret_cast<i16*>(membuf), sfinfo.frames);
      else if(sample_format == Float)
         frames = sf_readf_float(sndfile, reinterpret_cast<float*>(membuf), sfinfo.frames);
      else{
         sf_count_t count = sfinfo.frames / sampleBlockAlign * byteBlockAlign;
         frames = sf_read_raw(sndfile, membuf, count);
         if(frames > 0)
            frames = frames / byteBlockAlign * sampleBlockAlign;
      }

      if(frames < 1){
         free(membuf);
         sf_close(sndfile);
         std::cerr <<"failed to read samples in: " << filename << frames << "\n";
         return 0;
      }
      
      bytes = (ALsizei)(frames / sampleBlockAlign * byteBlockAlign);
      
      std::cout << "Loading: " << filename << " " << formatName(format) << " " << sfinfo.samplerate << std::endl;
      
      //buffer data => free data => close file
      
      buffer = 0;
      alGenBuffers(1, &buffer);
      if(sampleBlockAlign > 1){
         alBufferi(buffer, AL_UNPACK_BLOCK_ALIGNMENT_SOFT, sampleBlockAlign);
      }
      alBufferData(buffer, format, membuf, bytes, sfinfo.samplerate);

      free(membuf);
      sf_close(sndfile);

      //check for errors and clean
      err = alGetError();
      if(err != AL_NO_ERROR){
         std::cerr << "OpenAL errors: " << alGetString(err) << "\n";
         if(buffer && alIsBuffer(buffer)){
            alDeleteBuffers(1, &buffer);
            return 0;
         }
      }
      return buffer;
      }

    bool soundBuffer::removeSound(const ALuint& buffer){
      auto it = soundBuffers.begin();
      while(it != soundBuffers.end()){
         if(*it == buffer){
            alDeleteBuffers(1, &*it);
            it = soundBuffers.erase(it);
            return true;
         }
         else{
            ++it;
         }
      }
         return false; //could not find sound to remove

    }

    soundBuffer::soundBuffer(){
      soundBuffers.clear();
    }
    
    soundBuffer::~soundBuffer(){
      alDeleteBuffers(soundBuffers.size(), soundBuffers.data());
      soundBuffers.clear();
    }




} //snd namespace
