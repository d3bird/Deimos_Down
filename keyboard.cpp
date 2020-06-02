#include "keyboard.h"


keyboard::keyboard(Camera* c) {
	deltaTime = 0;
	camera = c;
	def_layout();
}

keyboard::~keyboard() {

}

void keyboard::process_key(unsigned char key, int mousex, int mousey) {

	//std::map<unsigned char, int>::iterator it2;
	//for (it2 = keys.begin(); it2 != keys.end(); ++it2) {
	//	std::cout << it2->first << " => " << it2->second << '\n';
	//}

	std::map<unsigned char, int>::iterator it;
	it = keys.find(key);
	if (it == keys.end()) {
		std::cout << key<<" not bounded" << std::endl;
		return;
	}
	else {
		std::cout << key << " was bounded to "<< keys.find(key)->second << std::endl;
	}
	std::cout << "prossecing key" << std::endl;
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
	default:
		std::cout << key << " ca" << std::endl;
		break;
	}
	
}

void keyboard::bind_key(unsigned char key, int custom) {//for the custom functions
	std::map<char, int>::iterator it;
	
	
}

void keyboard::def_layout() {
	/*keys['27'] = 0;
	keys['q'] = 0;
	keys['w'] = 1;
	keys['s'] = 2;
	keys['a'] = 3;
	keys['d'] = 4;
	keys[' '] = 5;
	keys['z'] = 6;*/
	std::cout << "creating a keybpard layout" << std::endl;
	keys.insert(std::pair<unsigned char, int>('q', 0));
	keys.insert(std::pair<unsigned char, int>('w', 1));
	keys.insert(std::pair<unsigned char, int>('s', 2));
	keys.insert(std::pair<unsigned char, int>('a', 3));
	keys.insert(std::pair<unsigned char, int>('d', 4));
	keys.insert(std::pair<unsigned char, int>(' ', 5));
	keys.insert(std::pair<unsigned char, int>('z', 6));
	std::map<unsigned char, int>::iterator it;
	for (it = keys.begin(); it != keys.end(); ++it) {
		std::cout << it->first << " => " << it->second << '\n';
	}
	unsigned char in = 'a';
	it = keys.find(in);
	if (it == keys.end()) {
		std::cout << 'a' << " not bounded" << std::endl;
		return;
	}
	else {
		std::cout << keys.find('a')->second << " was bounded" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
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