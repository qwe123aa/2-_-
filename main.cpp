#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace sf;

struct Textures {
	Texture dino_def;
};

class Dinosaur {
public:
	Sprite dino;

	Dinosaur(int speed) : speed_(speed) {

	}

private:
	int speed_;

};

const int gravity = 5;

const int WIDTH = 800;
const int HEIGHT = 500;
const int DINO_WIDTH = 200;
const int DINO_HEIGHT = 200;

int main(void) {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Project");
	window.setFramerateLimit(30);
	
	Textures tex;
	tex.dino_def.loadFromFile("./resource/dino_def.png");

	Dinosaur dinosaur = Dinosaur(40);
	dinosaur.dino.setTexture(tex.dino_def);
	dinosaur.dino.setPosition(WIDTH/2 - DINO_WIDTH, HEIGHT/2 - 50);
	dinosaur.dino.setScale(Vector2f(0.5f, 0.5f));
	
	while (window.isOpen()){
		Event e;
		while (window.pollEvent(e))
		{
			// 윈도우의 x를 눌렀을 때 창이 닫아지도록
			if (e.type == Event::Closed)
				window.close();
		}


		window.clear();

		window.draw(dinosaur.dino);

		window.display();
	}

}