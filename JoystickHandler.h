#include "Globals.h"

#ifndef  JOYSTICK_H
#define JOYSTICK_H

class JoystickHandler
{
public:
	JoystickHandler();
	~JoystickHandler();

	void process();

	void getButtonPressed(unsigned int button, int id);
	void getButtonReleased(unsigned int button, int id);
	void getStickMovement(float x, int id, sf::Joystick::Axis axis);

	bool getGas();
	bool getBrake();
	bool getBoost();
	bool getLeft();
	bool getRight();
	bool getUp();
	bool getDown();
	bool getStart();

	bool getb1();
	bool getb2();
	bool getb3();

private:
	
	bool gasPressed;
	bool brakePressed;
	bool boostPressed;

	bool b1pressed;
	bool b2pressed;
	bool b3pressed;

	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

	bool leftTriggerPressed;
	bool rightTriggerPressed;

	bool startPressed;

	unsigned int gas;
	unsigned int brake;
	unsigned int boost;

	unsigned int start;
};

#endif // ! JOYSTICK_H


