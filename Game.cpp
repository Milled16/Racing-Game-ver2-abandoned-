#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	running = true;
	joyStickEvent = false;
	hitchcock.create(sf::VideoMode(XRES, YRES), "Average Falloff");
	hitchcock.setSize(sf::Vector2u(XRES * 3, YRES * 3));
	hitchcock.setPosition(sf::Vector2i(100, 100));

	sf::View view1(sf::FloatRect(0, 0, XRES, YRES));
	hitchcock.setView(view1);

	timeSinceLastUp = 0.f;
	updateTimes = 0;

	leftPressed = false;
	rightPressed = false;
	upPressed = false;
	downPressed = false;

	gameText.loadFromFile("res/sprites/text.png");
	fps.setTexture(&gameText);
	theWordFps.setTexture(&gameText);
	theWordFps.setText("fps", sf::Vector2f(5, 0));
	theWordFps.setColor(sf::Color::Red);
	fps.setText(0, sf::Vector2f(0, 0));
	fps.setColor(sf::Color::Red);
}


Game::~Game()
{
}

void Game::process(float delta)
{
	while (hitchcock.pollEvent(evangelionSucks))
	{
		if (evangelionSucks.type == sf::Event::Closed)
		{
			hitchcock.close();
			running = false;
		}
		else if (evangelionSucks.type == sf::Event::KeyPressed)
		{
			joyStickEvent = false;
			if (evangelionSucks.key.code == sf::Keyboard::Escape)
			{
				running = false;
			}
			else if (evangelionSucks.key.code == sf::Keyboard::Up)
			{
				upPressed = true;
			}
			else if (evangelionSucks.key.code == sf::Keyboard::Down)
			{
				downPressed = true;
			}
			else if (evangelionSucks.key.code == sf::Keyboard::Left)
			{
				leftPressed = true;
			}
			else if (evangelionSucks.key.code == sf::Keyboard::Right)
			{
				rightPressed = true;
			}
		}
		else if (evangelionSucks.type == sf::Event::KeyReleased)
		{
			joyStickEvent = false;
			if (evangelionSucks.key.code == sf::Keyboard::Up)
			{
				upPressed = false;
			}
			else if (evangelionSucks.key.code == sf::Keyboard::Down)
			{
				downPressed = false;
			}
			else if (evangelionSucks.key.code == sf::Keyboard::Left)
			{
				leftPressed = false;
			}
			else if (evangelionSucks.key.code == sf::Keyboard::Right)
			{
				rightPressed = false;
			}
		}
		else if (evangelionSucks.type == sf::Event::JoystickMoved)
		{
			joyHandler.getStickMovement(sf::Joystick::getAxisPosition(evangelionSucks.joystickMove.joystickId, evangelionSucks.joystickMove.axis),
				evangelionSucks.joystickMove.joystickId,
				evangelionSucks.joystickMove.axis);
			joyStickEvent = true;
		}
		else if (evangelionSucks.type == sf::Event::JoystickButtonPressed)
		{
			joyHandler.getButtonPressed(evangelionSucks.joystickButton.button, evangelionSucks.joystickButton.joystickId);
			joyStickEvent = true;
		}
		else if (evangelionSucks.type == sf::Event::JoystickButtonReleased)
		{
			joyHandler.getButtonReleased(evangelionSucks.joystickButton.button, evangelionSucks.joystickButton.joystickId);
			joyStickEvent = true;
		}
	}
	joyHandler.process();

	if (!joyStickEvent)
		raceTrack.process(leftPressed, rightPressed, upPressed, downPressed);
	else
		raceTrack.process(joyHandler.getLeft(), joyHandler.getRight(), joyHandler.getGas(), joyHandler.getBrake());
}

void Game::update(float delta)
{

	raceTrack.update(delta);
}

void Game::render()
{
	hitchcock.clear();
	raceTrack.render(hitchcock);
	fps.render(hitchcock);
	theWordFps.render(hitchcock);
	hitchcock.display();
}



void Game::run()
{
	while (running)
	{

		deltaTime = cock.restart().asSeconds();
		timeSinceLastUp += deltaTime;
		process(deltaTime);
		update(deltaTime);
		render();
		updateTimes++;

		if (timeSinceLastUp >= 1.f)
		{
			fps.setText(updateTimes);
			theWordFps.setPosition(sf::Vector2f(5 + fps.getWidth(), 0));
			updateTimes = 0;
			timeSinceLastUp = 0.f;
		}
	}
	hitchcock.close();
}

float Game::clamp(float num, float min, float max)
{
	if (num < min)
		return min;
	else if (num > max)
		return max;
	else
		return num;
}