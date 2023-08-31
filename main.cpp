#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace sf;

struct Textures {
	Texture runner_def;
};

class Runner {
public:
	Sprite sprite;

	Runner(int speed) : speed_(speed) {

	}

private:
	int speed_;

};

const int gravity = 20;

const int WIDTH = 1000;
const int HEIGHT = 750;
const int START_X = 170;
const int START_Y = 350;

int main(void) {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Project");
	window.setFramerateLimit(60);
	Clock clock;

	//�ؽ���
	Textures tex;
	tex.runner_def.loadFromFile("./resource/runner_def.png");
	

	Runner runner = Runner(40);
	runner.sprite.setTexture(tex.runner_def);
	runner.sprite.setPosition(START_X, START_Y);
	
	while (window.isOpen()){
		Event e;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		//â�ݱ�
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		//����
		if (Keyboard::isKeyPressed(Keyboard::Space)) {

		}

		window.clear(Color::White);

		window.draw(runner.sprite);

		window.display();
	}

}