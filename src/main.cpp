#include "headers.hpp"
#include "snd/soundDevice.hpp"
#include "snd/soundBuffer.hpp"
#include "snd/soundSource.hpp"
#include "gfx/window.hpp"
#include "gfx/vkInstance.hpp"


int main() {
    snd::soundDevice * audioDevice = snd::soundDevice::get();
    u32 sound2 = snd::soundBuffer::get()->addSound("./sound/Lacrimosa.ogg");
    snd::soundSource speaker;
    gfx::window * screen = gfx::window::get(800,600,"gameEngine");
    gfx::vkInstance * instance  = gfx::vkInstance::get();

    speaker.play(sound2);

    while(!screen->shouldClose()){
        glfwPollEvents();



    }












return 0;
}
