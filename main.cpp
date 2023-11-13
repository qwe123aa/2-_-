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

	Texture hurdle_mini;
	Texture hurdle_big;
	Texture hurdle_sky;
};

class Runner {
public:
	Runner(int gravity, int jumping) : gravity_(gravity), jumping_(jumping) {

	}

	Sprite sprite;

	int getGravity() {
		return gravity_;
	}

	void setGravity(int gravity) {
		gravity_ = gravity;
	}

	int getJumping() {
		return jumping_;
	}

	void setJumping(int jumping) {
		jumping_ = jumping;
	}

private:
	int gravity_;
	int jumping_;
};

class Hurdle {
public:
	Sprite sprite;

	Hurdle(int speed) : speed_(speed) {

	}

	int getSpeed() {
		return speed_;
	}

	void setSpeed(int speed) {
		speed_ = speed;
	}

	void update() {
		sprite.move(-speed_, 0);
	}


private:
	int speed_;
};

int layer = 0;
const int max_speed = 20;

const int WIDTH = 1000;
const int HEIGHT = 750;
const int START_X = 130;
const int START_Y = 310;
const int Ceiling = START_Y - 200;

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
	
	tex.hurdle_mini.loadFromFile("./resource/hurdle/hurdle_mini.png");
	tex.hurdle_big.loadFromFile("./resource/hurdle/hurdle_big.png");
	tex.hurdle_sky.loadFromFile("./resource/hurdle/hurdle_sky.png");

	//선언
	Runner runner = Runner(25, -50);
	runner.sprite.setTexture(tex.runner_def);
	runner.sprite.setPosition(START_X, START_Y);

	Hurdle hurdle_big = Hurdle(12);
	hurdle_big.sprite.setTexture(tex.hurdle_big);
	hurdle_big.sprite.setPosition(START_X + WIDTH, START_Y+166-140);

	Hurdle hurdle_mini = Hurdle(12);
	hurdle_mini.sprite.setTexture(tex.hurdle_mini);
	hurdle_mini.sprite.setPosition(START_X + WIDTH + 600, START_Y+166-69);

	Hurdle hurdle_sky = Hurdle(12);
	hurdle_sky.sprite.setTexture(tex.hurdle_sky);
	hurdle_sky.sprite.setPosition(START_X + WIDTH + 1400, Ceiling);


	
	while (window.isOpen()){
		Event e;
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		mouse_pos = Mouse::getPosition(window);
		Vector2f runner_pos = runner.sprite.getPosition();
		bool onGround = true;
		bool isJumping = false;

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

		//플레이중 
		if (layer == 1) {
			if (walk_timer.getElapsedTime() > walk_time) {
				runner.sprite.setTexture(tex.runner_run);
			}
			if (walk_timer.getElapsedTime() > walk_time2) {
				runner.sprite.setTexture(tex.runner_def);

				walk_timer.restart();
			}

			//점프
			if (Keyboard::isKeyPressed(Keyboard::Space) && !isJumping) {
				isJumping = true;
			}

			if (isJumping == true) {
				runner.sprite.move(0, runner.getJumping());
			}

			runner.sprite.move(0,runner.getGravity());


			if (runner.sprite.getPosition().y >= START_Y) {
				runner.sprite.setPosition(runner.sprite.getPosition().x, START_Y);
				isJumping = false;
			}

			if (runner.sprite.getPosition().y <= Ceiling) {
				runner.sprite.setPosition(runner.sprite.getPosition().x, Ceiling);
				isJumping = false;
			}

			//적
			hurdle_big.update();
			hurdle_mini.update();
			hurdle_sky.update();

			if (hurdle_big.sprite.getPosition().x <= -100)
				hurdle_big.sprite.setPosition(START_X + WIDTH, START_Y + 166 - 140);

			if (hurdle_mini.sprite.getPosition().x <= -100)
				hurdle_mini.sprite.setPosition(START_X + WIDTH, START_Y + 166 - 69);

			if (hurdle_sky.sprite.getPosition().x <= -100)
				hurdle_sky.sprite.setPosition(START_X + WIDTH, Ceiling);
		}


		window.clear();

		if (layer == 0) {
			window.draw(title);
			window.draw(btnStart);
		}

		if (layer == 1) {
			window.draw(background);
			window.draw(hurdle_big.sprite);
			window.draw(hurdle_mini.sprite);
			window.draw(hurdle_sky.sprite);
			window.draw(runner.sprite);
		}

		window.display();
	}

}