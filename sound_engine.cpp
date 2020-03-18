#include "sound_engine.h"

using namespace irrklang;

sound_engine::sound_engine() {
	sound = "resources/media/bell.wav";
	music = "resources/media/getout.ogg";
	initated = false;
	engine = createIrrKlangDevice();
	if (!engine)
	{
		printError();
	}
	else {
		initated = true;
		std::cout << "playing sound" << std::endl;
		engine->play2D(sound.c_str());
	}

}

sound_engine::~sound_engine() {
	engine->drop();
}


void sound_engine::play_background() {
	engine->play2D(music.c_str(), true);
}

void sound_engine::play_sound() {
	engine->play2D(sound.c_str(), true);
}