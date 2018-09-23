#include "sRaceTrack.h"
#include "JoystickHandler.h"
#include "Globals.h"
#include "SpriteText.h"

#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Game();
	~Game();

	void process(float delta);
	void update(float delta);
	void render();

	void run();

	float clamp(float num, float min, float max);
private:
	sf::Clock cock;
	float deltaTime;
	float timeSinceLastUp;
	int updateTimes;

	sf::Texture gameText;
	SpriteText fps;
	SpriteText theWordFps;

	sf::Event evangelionSucks;

	sf::RenderWindow hitchcock;

	bool leftPressed, rightPressed, upPressed, downPressed;
	bool running;

	sRaceTrack raceTrack;
	JoystickHandler joyHandler;
	sf::Joystick joy;
	bool joyStickEvent;
};

#endif // !GAME_H

