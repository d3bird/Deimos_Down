#pragma once
#include <irrklang/irrKlang.h>
#include <conio.h>

#include <string>
#include <iostream>


class sound_engine {
public:

	sound_engine();
	~sound_engine();

	void play_background();
	void play_sound();

	bool isrunnning() { return initated; }

private:

	void printError() { std::cout << "could not start engine" << std::endl; }

	bool initated;
	std::string sound;
	std::string music;
	irrklang::ISoundEngine* engine;
};

