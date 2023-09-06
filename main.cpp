#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace sf;

struct Textures {
	Texture title;
	Texture btnStart;
	Texture btnStart_sel;

	Texture background;
	Texture runner_def;
	Texture runner_run;
};

class Runner {
public:
	Sprite sprite;

	Runner(int speed, float run_sit) : speed_(speed) {

	}

private:
	int speed_;
};

int layer = 0;
const int gravity = 20;

const int WIDTH = 1000;
const int HEIGHT = 750;
const int START_X = 130;
const int START_Y = 310;

int main(void) {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "chrome://human");
	window.setFramerateLimit(60);
	Clock clock;
	Clock walk_timer;
	Vector2i mouse_pos;

	const Time walk_time = seconds(0.1f);
	const Time walk_time2 = seconds(0.2f);

	//텍스쳐
	Textures tex;
	tex.title.loadFromFile("./resource/background/title.png");
	tex.btnStart.loadFromFile("./resource/button/btnStart.png");
	tex.btnStart_sel.loadFromFile("./resource/button/btnStart_sel.png");
	
	tex.background.loadFromFile("./resource/background/background.png");
	tex.runner_def.loadFromFile("./resource/character/runner_def.png");
	tex.runner_run.loadFromFile("./resource/character/runner_run.png");
	

	Runner runner = Runner(40, 1);
	runner.sprite.setTexture(tex.runner_def);
	runner.sprite.setPosition(START_X, START_Y);
	
	while (window.isOpen()){
		Event e;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		mouse_pos = Mouse::getPosition(window);

		//창닫기
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}

		//시작화면
		Sprite title;
		title.setTexture(tex.title);
		title.setPosition(0, 0);

		Sprite btnStart;
		btnStart.setTexture(tex.btnStart);
		btnStart.setPosition(WIDTH / 2 - 125, HEIGHT / 2 + 20);

		if (layer == 0) {
			if (btnStart.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y)) {
				btnStart.setTexture(tex.btnStart_sel);
				
				if (Mouse::isButtonPressed(Mouse::Left)) {
					layer = 1;
				}
			}

		}

		//게임화면
		Sprite background;
		background.setTexture(tex.background);
		background.setPosition(0, 0);

		if (layer == 1) {
			if (walk_timer.getElapsedTime() > walk_time) {
				runner.sprite.setTexture(tex.runner_run);
			}
			if (walk_timer.getElapsedTime() > walk_time2) {
				runner.sprite.setTexture(tex.runner_def);

				walk_timer.restart();
			}

			//점프
			if (Keyboard::isKeyPressed(Keyboard::Space)) {

			}
		}

		window.clear();

		if (layer == 0) {
			window.draw(title);
			window.draw(btnStart);
		}

		if (layer == 1) {
			window.draw(background);
			window.draw(runner.sprite);
		}

		window.display();
	}

}