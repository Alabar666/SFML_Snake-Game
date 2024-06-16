#include "snake.hpp"
#include "game.hpp"
#include <Windows.h>
#include <time.h>

//TODO PERDER O GAME SE BATER NA PROPRIA CAUDA
// VERIFICAR SE A NOVA POSICAO DA FRUIT ESTA DENTRO DA CAUDA





SnakeGame s[100];
Fruit fruit;

Snake::Snake() {
	cols = 20;
	lines = 13;
	size = 64;
	width = size * cols;
	height = size * lines;
	direction = 0;
	num = 4;
	timer = 0.f;
	delay = 0.1f;
	fruit.x = fruit.y = 10;

	window.create(sf::VideoMode(width, height), "Snake Game 1.0", sf::Style::Titlebar | sf::Style::Close);

	t1.loadFromFile("./bg.png");
	t2.loadFromFile("./assets/img/snake.png");
	t3.loadFromFile("./assets/img/fruta.png");

	sp1.setTexture(t1);
	sp2.setTexture(t2);
	sp3.setTexture(t3);
}

void Snake::run_game() {
	while (window.isOpen()) {

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (timer > delay) {
			timer = 0;
			collision();
		}

		window.clear();

		for (int i = 0; i < cols; ++i) {
			for (int j = 0; j < lines; ++j) {
				sp1.setPosition(i * size, j * size);
				window.draw(sp1);
			}
		}
		for (int i = 0; i < num; ++i) {
			sp2.setPosition(s[i].x * size, s[i].y * size);
			window.draw(sp2);
		}

		sp3.setPosition(fruit.x * size, fruit.y * size);
		window.draw(sp3);

		window.display();
	}
}

void Snake::collision() {

	for (int i = num; i > 0; --i) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (direction != 1)
			direction = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (direction != 0)
			direction = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (direction != 3)
			direction = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (direction != 2)
			direction = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (direction != 1)
			direction = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (direction != 0)
			direction = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (direction != 3)
			direction = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (direction != 2)
			direction = 3;
	}
	switch (direction) {
	case 0:
		s[0].x += 1;
		break;
	case 1:
		s[0].x -= 1;
		break;
	case 2:
		s[0].y -= 1;
		break;
	case 3:
		s[0].y += 1;
		break;
	}

	for (int i = 1; i < num; ++i) {
		if (s[0].x == s[i].x && s[0].y == s[i].y) {
			Sleep(3000);
			window.close();
			break;
		}
	}

	if (s[0].y == fruit.y && s[0].x == fruit.x || s[1].y == fruit.y && s[1].x == fruit.x) {
		++num;
		bool valid_position;
		do {
			valid_position = true;
			fruit.x = std::rand() % cols;
			fruit.y = std::rand() % lines;
			for (int i = 0; i < num; ++i) {
				if (s[i].x == fruit.x && s[i].y == fruit.y)
				{
					valid_position = false;
					break;
				}
			}
		} while (!valid_position);
	}
	
	if (s[0].x >= cols) {
		s[0].x = 0;
	}
	if (s[0].x < 0) {
		s[0].x = cols - 1;
	}
	if (s[0].y >= lines) {
		s[0].y = 0;
	}
	if (s[0].y < 0) {
		s[0].y = lines - 1;
	}

}


