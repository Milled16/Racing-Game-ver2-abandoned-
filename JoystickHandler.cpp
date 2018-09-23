#include "stdafx.h"
#include "JoystickHandler.h"


JoystickHandler::JoystickHandler()
{
	gasPressed = false;
	brakePressed = false;
	boostPressed = false;

	b1pressed = false;
	b2pressed = false;
	b3pressed = false;

	leftPressed = false;
	rightPressed = false;
	upPressed = false;
	downPressed = false;

	startPressed = false;

	leftTriggerPressed = false;
	rightTriggerPressed = false;

	gas = 0;
	brake = 1;
	boost = 2;

	start = 7;
}


JoystickHandler::~JoystickHandler()
{
}

void JoystickHandler::process()
{
	if (b1pressed || rightTriggerPressed)
		gasPressed = true;
	else
		gasPressed = false;

	if (b2pressed || leftTriggerPressed)
		brakePressed = true;
	else
		brakePressed = false;
}

void JoystickHandler::getButtonPressed(unsigned int button, int id)
{
	if (id == 0)
	{
		if (button == gas)
			b1pressed = true;
		else if (button == brake)
			b2pressed = true;
		else if (button == boost)
			boostPressed = true;
		else if (button == start)
			startPressed = true;
	}
}

void JoystickHandler::getButtonReleased(unsigned int button, int id)
{
	if (id == 0)
	{
		if (button == gas)
			b1pressed = false;
		else if (button == brake)
			b2pressed = false;
		else if (button == boost)
			boostPressed = false;
		else if (button == start)
			startPressed = false;
	}
}

void JoystickHandler::getStickMovement(float x, int id, sf::Joystick::Axis axis)
{
	if (id == 0)
	{
		if (axis == sf::Joystick::Axis::X)
		{
			if (x > 40.f)
				rightPressed = true;
			else
				rightPressed = false;

			if (x < -40.f)
				leftPressed = true;
			else
				leftPressed = false;
		}
		else if (axis == sf::Joystick::Axis::Y)
		{
			if (x > 40.f)
				downPressed = true;
			else
				downPressed = false;

			if (x < -40.f)
				upPressed = true;
			else
				upPressed = false;
		}
		else if (axis == sf::Joystick::Axis::Z)
		{
			if (x > 40.f)
				leftTriggerPressed = true;
			else
				leftTriggerPressed = false;

			if (x < -40.f)
				rightTriggerPressed = true;
			else
				rightTriggerPressed = false;
		}
	}
}

bool JoystickHandler::getGas()
{
	return gasPressed;
}

bool JoystickHandler::getBrake()
{
	return brakePressed;
}

bool JoystickHandler::getBoost()
{
	return boostPressed;
}

bool JoystickHandler::getLeft()
{
	return leftPressed;
}

bool JoystickHandler::getRight()
{
	return rightPressed;
}

bool JoystickHandler::getUp()
{
	return upPressed;
}

bool JoystickHandler::getDown()
{
	return downPressed;
}

bool JoystickHandler::getStart()
{
	return startPressed;
}

bool JoystickHandler::getb1()
{
	return b1pressed;
}

bool JoystickHandler::getb2()
{
	return b2pressed;
}

bool JoystickHandler::getb3()
{
	return b3pressed;
}
