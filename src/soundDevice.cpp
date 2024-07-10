#include "soundDevice.hpp"


namespace snd {
    soundDevice* soundDevice::get(){
        static soundDevice* snd_device = new soundDevice(); 
        return snd_device;
    }
    
    soundDevice::soundDevice(){
        device = alcOpenDevice(nullptr); //get default sound device

        if(!device){
            throw std::runtime_error("failed to get sound device");
        }
        
        context = alcCreateContext(device, nullptr); //create alc sound context
        
        if(!context){
            throw std::runtime_error("failed to set sound context");
        }

        if(!alcMakeContextCurrent(context)){ //make context current context
            throw std::runtime_error("failed to make context current");
        }

        const ALCchar* name = nullptr;
        if(alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT")){
            name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
        }
        if(!name || alcGetError(device) != AL_NO_ERROR){
            name = alcGetString(device, ALC_DEVICE_SPECIFIER);
        }
        std::cout << "audio device:\n" << name;
    }

    soundDevice::~soundDevice(){
    }

    
} // namespace snd
    
