#include "headers.hpp"
#include "snd/soundDevice.hpp"
#include "snd/soundBuffer.hpp"
#include "snd/soundSource.hpp"
#include "gfx/window.hpp"


int main() {
    snd::soundDevice * audioDevice = snd::soundDevice::get();
    u32 sound2 = snd::soundBuffer::get()->addSound("./sound/Lacrimosa.ogg");
    snd::soundSource speaker;
    gfx::window * screen = gfx::window::get(800,600,"gameEngine");

    speaker.play(sound2);

    std::cout << "loop starting\n";
    while(!screen->shouldClose()){ 

        glfwPollEvents(); 

    }

    std::cout << "loop ending\n";











return 0;
}
