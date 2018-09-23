#include "stdafx.h"
#include "sRaceTrack.h"


sRaceTrack::sRaceTrack()
{
	state = Normal;
	speed = 0.f;
	animationTime = 0.f;
	numOfBackgrounds = 2;
	currentBackground = 0;

	farBackTextY[0] = 0;
	farBackTextY[1] = 120;

	farBackTextHeight[0] = 120;
	farBackTextHeight[1] = 180;

	nearBackTextY[0] = 0;
	nearBackTextY[1] = 120;

	nearBackTextHeight[0] = 120;
	nearBackTextHeight[1] = 120;

	nearBackgroundTexture.loadFromFile("res/sprites/test near background.png");
	nearBackgroundTexture.setRepeated(true);
	bg.bgNear.setTexture(nearBackgroundTexture);
	bg.bgNear.setOrigin(sf::Vector2f(640, nearBackTextHeight[0]));

	farBackgroundTexture.loadFromFile("res/sprites/test far background.png");
	farBackgroundTexture.setRepeated(true);
	bg.bgFar.setTexture(farBackgroundTexture);
	bg.bgFar.setOrigin(320, farBackTextHeight[0]);

	bg.bottom.setTexture(farBackgroundTexture);
	bg.bottom.setOrigin(320, 0);

	bg.nearScale = THE_D / 12.f;
	bg.farScale = THE_D / 24.f;
	bgNearX = 0;
	bgY = 0;
	bgFarX = 0;

	numOfCourses = 0;
	numOfForks = 0;

	currentSegment = 0;
	loadRoadData("res/levelData/track1.txt");
	int totalSize = 0;
	for (int i = 0; i < mainCourse.size(); i++)
	{
		totalSize += mainCourse[i].length;
	}

	objectHandler.loadFromFile(file, "res/levelData/objects1.txt", totalSize);

	mainRoad.setRoadType(mainCourse[currentSegment].roadType);
	for (int i = 0; i < MAX_SEGMENTS; i++)
	{
		mainRoad.addSegment(0, 0, 0, 0, 0, 0, 0);
	}

	eveningSky.setFillColor(sf::Color(0, 50, 125));
	eveningSky.setSize(sf::Vector2f(XRES, YRES));
	eveningSky.setPosition(sf::Vector2f(0, 0));

}


sRaceTrack::~sRaceTrack()
{
}

void sRaceTrack::process(bool leftPressed, bool rightPressed, bool upPressed, bool downPressed)
{
	if (leftPressed)
		turnAmount = 0 - MAX_MOVE_SPEED;
	else if (rightPressed)
		turnAmount = MAX_MOVE_SPEED;
	else turnAmount = 0.f;

	if (upPressed)
		accelAmount = ACCELERATION;
	else
		accelAmount = 0 - ACCELERATION;

	if (downPressed)
		brakeAmount = BRAKE_SPEED;
	else
		brakeAmount = 0;

	accelAmount -= brakeAmount;
}

void sRaceTrack::update(float delta)
{
	animationTime += delta;
	while (animationTime >= ANIMATION_TIME.asSeconds())
	{
		//mainRoad.animateGrass();
		animationTime -= ANIMATION_TIME.asSeconds();
	}

	float dCamX, dCamY, dx, dy, camHeight;
	speed += accelAmount * delta;
	speed = clamp(speed, 0.f, SPEED_LIMIT);
	camX += (turnAmount * delta) * speed;

		mainRoad.update(speed, delta);
		//riderHandler.update(delta, speed);

		for (int i = mainRoad.size() - 1; i > 0; i--)
		{
			//riderHandler.placeObjects(mainRoad[i - 1], mainRoad[i]);
		}

		while (mainRoad.segOverThreshold())
		{
			mainRoad.eraseFirstSegment();
			objectHandler.removeFirstSet();

			if (mainCourse.size() > 0 && mainCourse[currentSegment].length > 0)
			{
				mainRoad.addSegment(mainCourse[currentSegment].roadSegs[0].x, mainCourse[currentSegment].roadSegs[0].y, mainCourse[currentSegment].roadSegs[0].ddx, mainCourse[currentSegment].roadSegs[0].ddy,
					mainCourse[currentSegment].roadSegs[0].nearBackgroundRotate, mainCourse[currentSegment].roadSegs[0].farBackgroundRotate, mainCourse[currentSegment].roadSegs[0].backgroundY);

				mainCourse[currentSegment].length--;

				mainCourse[currentSegment].roadSegs.erase(mainCourse[currentSegment].roadSegs.begin());
				
			}
			else if (mainCourse.size() > 0 && mainCourse[currentSegment].length <= 0)
			{
				mainCourse.erase(mainCourse.begin());
				if (currentBackground + 1 < numOfBackgrounds)
				{
					currentBackground++;

					bg.bgFar.setOrigin(320, farBackTextHeight[currentBackground]);
					bg.bgNear.setOrigin(640, nearBackTextHeight[currentBackground]);
				}

				if (mainCourse.size() > 0)
				{
					mainRoad.setRoadType(mainCourse[currentSegment].roadType);
				}
			}
			else if(currentSegment >= mainCourse.size())
			{
				mainRoad.addRepeatSegment();
			}
		}

		percentage = mainRoad.getPercentage();

	projectRoad();
	projectBackground();
}

void sRaceTrack::render(sf::RenderWindow & window)
{
	int i = mainRoad.size() - 1;

	window.draw(eveningSky);
	window.draw(bg.bgFar);
	window.draw(bg.bgNear);
	window.draw(bg.bottom);
	while (i >= 0 && state == Normal)
	{
		mainRoad.render(window, i);
		objectHandler.render(window, i);
		//riderHandler.render(window, mainRoad[i].z1, mainRoad[i].z2);
		i--;
	}
	//riderHandler.debugRender(window);
}

void sRaceTrack::loadRoadData(std::string fileName)
{
	file.openRoadFile(fileName);

	while (!file.eof())
	{
		mainCourse.push_back(tempSeg);
		file.loadRoadData(mainCourse[numOfCourses]);
		
		numOfCourses++;
	}
}

void sRaceTrack::projectRoad()
{
	mainRoad.calculateDX();
	mainRoad.calculateDY();
	int i = 0;

	float dCamX, dCamY, dx, dy;
	dCamX = camX;
	//dCamY = camY + mainRoad[5].y + (mainRoad[6].y - mainRoad[5].y) * percentage;

	//dx = 0 - (mainRoad[0].ddx * percentage);

	//dy = 0 - (mainRoad[0].ddy * percentage);

	//dCamX += dx;
	//dCamY += dy;

	while (i < mainRoad.size() && state == Normal)
	{
		mainRoad.project(camX, camY, camZ, i);
		objectHandler.placeObjects(i, mainRoad.getXY(i), mainRoad[i].scale);

		//dx += mainRoad[i].ddx;
		//dy += mainRoad[i].ddy;
		//dCamX += dx;
		//dCamY += dy;
		i++;
	}
}

void sRaceTrack::projectBackground()
{
	float xCam, yCam, xProj, yProj, xScreen, yScreen, turnSpeed;

	bgNearX = mainRoad[0].nearBackgroundRotate + (mainRoad[1].nearBackgroundRotate - mainRoad[0].nearBackgroundRotate) * percentage;
	bgFarX = mainRoad[0].farBackgroundRotate + (mainRoad[1].farBackgroundRotate - mainRoad[0].farBackgroundRotate) * percentage;
	bgY = mainRoad[0].backgroundY + (mainRoad[1].backgroundY - mainRoad[0].backgroundY) * percentage;

	xCam = 0 - camX;
	yCam = bgY - camY;

	xProj = xCam * bg.nearScale;
	yProj = yCam * bg.nearScale;

	xScreen = HALF_WIDTH + (HALF_WIDTH * xProj);
	yScreen = HALF_HEIGHT - (HALF_HEIGHT * yProj);

	bg.bgNear.setPosition(sf::Vector2f(xScreen, yScreen));
	bg.bottom.setPosition(sf::Vector2f(xScreen, yScreen));

	xProj = xCam * bg.farScale;
	yProj = yCam * bg.farScale;

	xScreen = HALF_WIDTH + (HALF_WIDTH * xProj);
	yScreen = HALF_HEIGHT - (HALF_HEIGHT * yProj);
	bg.bgFar.setPosition(sf::Vector2f(xScreen, yScreen));
	
	bg.bgNear.setTextureRect(sf::IntRect(bgNearX, nearBackTextY[currentBackground], 1280, nearBackTextHeight[currentBackground]));
	bg.bgFar.setTextureRect(sf::IntRect(bgFarX, farBackTextY[currentBackground], 640, farBackTextHeight[currentBackground]));
	bg.bottom.setTextureRect(sf::IntRect(bgNearX, nearBackTextY[currentBackground], 640, 240));
}

float sRaceTrack::clamp(float num, float min, float max)
{
	if (num < min)
		return min;
	else if (num > max)
		return max;
	else
		return num;
}
