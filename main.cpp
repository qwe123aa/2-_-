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
	Texture runner_def;
	Texture runner_run;
};

class Runner {
public:
	Sprite sprite;

	Runner(int speed, float run_sit) : speed_(speed), run_sit_(run_sit) {

	}

	float getRunSit(void) {
		return run_sit_;
	}

	void setRunSit(float run_sit) {
		run_sit = run_sit_;
	}

private:
	int speed_;
	float run_sit_;
};

int layer = 0;
const int gravity = 20;

const int WIDTH = 1000;
const int HEIGHT = 750;
const int START_X = 170;
const int START_Y = 350;

int main(void) {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Project");
	window.setFramerateLimit(60);
	Clock clock;
	Clock walk_timer;

	const Time walk_time = seconds(0.1f);

	//텍스쳐
	Textures tex;
	tex.title.loadFromFile("./resource/background/title.png");
	tex.btnStart.loadFromFile("./resource/button/btnStart.png");
	tex.btnStart_sel.loadFromFile("./resource/button/btnStart_sel.png");
	tex.runner_def.loadFromFile("./resource/character/runner_def.png");
	tex.runner_run.loadFromFile("./resource/character/runner_run.png");
	

	Runner runner = Runner(40, 1);
	runner.sprite.setTexture(tex.runner_def);
	runner.sprite.setPosition(START_X, START_Y);
	
	while (window.isOpen()){
		Event e;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

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


		//달리는 모습
		while (layer == 1) {
			if (walk_timer.getElapsedTime() > walk_time && runner.getRunSit() == 1) {
				runner.sprite.setTexture(tex.runner_run);
				runner.setRunSit(2);

				walk_timer.restart();
			}
			if (walk_timer.getElapsedTime() > walk_time && runner.getRunSit() == 2) {
				runner.sprite.setTexture(tex.runner_def);
				runner.setRunSit(1);

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
			window.draw(runner.sprite);
		}

		window.display();
	}

}