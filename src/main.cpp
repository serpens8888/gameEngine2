#include "headers.hpp"
#include "soundDevice.hpp"
#include "soundBuffer.hpp"
#include "soundSource.hpp"


int main() {
    snd::soundDevice * audioDevice = snd::soundDevice::get();
    u32 sound = snd::soundBuffer::get()->addSound("./sound/Lacrimosa.ogg");
    snd::soundSource speaker;
    speaker.play(sound);
    std::cin.get();










return 0;
}
