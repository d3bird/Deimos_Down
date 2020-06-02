#pragma once

#include <iostream>
#include <string>
#include <map>

#include "camera.h"
#include "world.h"


class keyboard {
public:
	keyboard(Camera* c);
	~keyboard();

	//for normal keys,
	void process_key(unsigned char key, int mousex, int mousey);

	void bind_key(unsigned char key, int func);//for the custom functions
	void upadate_time(float i) { deltaTime = i; }

	//setters
	void set_cam(Camera* c) { camera = c; }
	void set_world(world* w) { World = w; }

private:

	void def_layout();
	void add_debug_layout();
	void old_hard_coded_solution(unsigned char key);
	std::map<unsigned char, int> keys;


	Camera* camera;
	world* World;

	float deltaTime;//this is updated with the correct timing when the key is pressed

	//functions to interact witht the rest of the program
	inline void stop_prog() { exit(1); }
	inline void forward() { camera->ProcessKeyboard(FORWARD, deltaTime); }
	inline void backward() { camera->ProcessKeyboard(BACKWARD, deltaTime); }
	inline void left() { camera->ProcessKeyboard(LEFT, deltaTime); }
	inline void right() { camera->ProcessKeyboard(RIGHT, deltaTime); }
	inline void up() { camera->ProcessKeyboard(UP_D, deltaTime); }
	inline void down() {}

	//keyboard debug

	void print_keyboard_shortcuts();
};

