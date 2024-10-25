#include "headers.hpp"

#include "snd/soundDevice.hpp"
#include "snd/soundBuffer.hpp"
#include "snd/soundSource.hpp"
#include "snd/soundGen.hpp"
#include "snd/procedural/waveforms.hpp"

#include "gfx/window.hpp"

int main() {


    snd::soundDevice * audioDevice = snd::soundDevice::get();
    u32 sound = snd::soundBuffer::get()->addSound("./sound/Lacrimosa.ogg");

    snd::soundSource speaker;

    snd::speakerCreationData creationData;
    creationData.loopSound = true;
    creationData.gain = 2.0f;
    creationData.pitch = 1.0f;
    creationData.position = {1,0,0};
    creationData.velocity = {0,0,0};

    speaker.create(creationData);

    snd::generateSound wasd(snd::procedural::generateSineWave(32.70,10));

    speaker.play(wasd.buffer);

    snd::soundSource speaker2;
    speaker2.create({true, 2.0f, 1.0f, {-1,0,0}, {0,0,0}});
    snd::generateSound sound2(snd::procedural::generateSineWave(43.65,10));
    speaker2.play(sound2.buffer);


    gfx::window * screen = gfx::window::get(800,600,"gameEngine");



    std::cout << "loop starting\n";
    while(!screen->shouldClose()){ 

        glfwPollEvents(); 

    }

    std::cout << "loop ending\n";







return 0;
}
