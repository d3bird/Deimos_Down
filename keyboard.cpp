#include "keyboard.h"


keyboard::keyboard(Camera* c) {
	deltaTime = 0;
	camera = c;
	def_layout();
	add_debug_layout();
}

keyboard::~keyboard() {

}

void keyboard::process_key(unsigned char key, int mousex, int mousey) {


	std::map<unsigned char, int>::iterator it;
	it = keys.find(key);
	if (it == keys.end()) {
		return;
	}

	int command = it->second;

	switch (command){
	case 0:
		stop_prog();
		break;
	case 1:
		forward();
		break;
	case 2:
		backward();
		break;
	case 3:
		left();
		break;
	case 4:
		right();
		break;
	case 5:
		up();
		break;
	case 6:
		down();
		break;
	case 7:
		print_keyboard_shortcuts();
		break;
	default:
		std::cout << key << " ca" << std::endl;
		break;
	}
	
}

void keyboard::bind_key(unsigned char key, int func) {//for the custom functions
	std::map<unsigned char, int>::iterator it;
	it = keys.find(key);
	if (it == keys.end()) {
		keys.insert(std::pair<unsigned char, int>(key, func));
	}
	else {
		std::cout << "key already has a bound key, overriding " << std::endl;
	}
}

void keyboard::def_layout() {

	std::cout << "seting up def keyboard layout" << std::endl;
	keys.insert(std::pair<unsigned char, int>(27, 0));//the esc key
	keys.insert(std::pair<unsigned char, int>('q', 0));
	keys.insert(std::pair<unsigned char, int>('w', 1));
	keys.insert(std::pair<unsigned char, int>('s', 2));
	keys.insert(std::pair<unsigned char, int>('a', 3));
	keys.insert(std::pair<unsigned char, int>('d', 4));
	keys.insert(std::pair<unsigned char, int>(' ', 5));
	keys.insert(std::pair<unsigned char, int>('z', 6));

	//std::map<unsigned char, int>::iterator it;
	//for (it = keys.begin(); it != keys.end(); ++it) {
	//	std::cout << it->first << " => " << it->second << '\n';
	//}

	std::cout <<"finished binding keys"<< std::endl;
}

void keyboard::add_debug_layout() {
	std::cout << "adding in debug keys" << std::endl;
	keys.insert(std::pair<unsigned char, int>('1', 7));
	std::cout << "finnished ading debug keys" << std::endl;
}

//if there is ever a problem with the keyboard layout this can work as backup
void keyboard::old_hard_coded_solution(unsigned char key) {

	switch (key) {
	case 27://hitting the escape key
	case 'q':
		exit(0);
		break;
	case 'w':
		camera->ProcessKeyboard(FORWARD, deltaTime);
		break;
	case 's':
		camera->ProcessKeyboard(BACKWARD, deltaTime);
		break;
	case 'a':
		camera->ProcessKeyboard(LEFT, deltaTime);
		break;
	case 'd':
		camera->ProcessKeyboard(RIGHT, deltaTime);
		break;
	case ' ':
		camera->ProcessKeyboard(UP_D, deltaTime);
		break;
	case '1':
		World->toggleHud();
		break;
	default:
		// glutSetWindowTitle(key);
		break;
	}

	return;

}

//debug functions
void keyboard::print_keyboard_shortcuts() {
	std::map<unsigned char, int>::iterator it2;
	for (it2 = keys.begin(); it2 != keys.end(); ++it2) {
		std::string translation = "none";
		switch (it2->second) {
		case 0:
			translation = "stop program";
			break;
		case 1:
			translation = "move cam forward";
			break;
		case 2:
			translation = "move cam backward";
			break;
		case 3:
			translation = "move cam left";
			break;
		case 4:
			translation = "move cam right";
			break;
		case 5:
			translation = "move cam up";
			break;
		case 6:
			translation = "move cam down";
			break;
		case 7:
			translation = "print keyboard layout";
			break;
		}

		std::cout << it2->first << " => " << translation << '\n';
	}
}