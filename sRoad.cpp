#include "stdafx.h"
#include "sRoad.h"


sRoad::sRoad()
{
	grass.setSize(sf::Vector2f(XRES, YRES));
	grass.setOrigin(sf::Vector2f(0, 0));
	grass.setFillColor(sf::Color(0, 125, 80));

	roadSpriteSheet.loadFromFile("res/sprites/road.png");
	tempSeg.road.setTexture(roadSpriteSheet);
	tempSeg.road.setOrigin(sf::Vector2f(200, 0));
	setRoadType(4);
}


sRoad::~sRoad()
{
}

void sRoad::update(float speed, float delta)
{
	grassHeight = YRES;
	moveSegs(speed * delta);
}

void sRoad::render(sf::RenderWindow & window, int i)
{
	if (i == grassRender)
	{
		if (grassHeight < 0)
			grassHeight = 0;

		grass.setPosition(sf::Vector2f(0, grassHeight));
		window.draw(grass);
	}
	window.draw(segs[i].road);

	while (i > 0 && segs[i].road.getPosition().y < segs[i - 1].road.getPosition().y - segs[i - 1].road.getGlobalBounds().height)
	{
		segs[i].road.move(sf::Vector2f(0, segs[i].road.getGlobalBounds().height));
		window.draw(segs[i].road);
	}
}

void sRoad::debugRender(sf::RenderWindow & window)
{
}

void sRoad::calculateDX()
{
	float dx = 0 - (segs[0].ddx * getPercentage());
	float x = 0.f;

	for (int i = 0; i < segs.size(); i++)
	{
		segs[i].dx = x;
		dx += segs[i].ddx;
		x += dx;
	}
}

void sRoad::calculateDY()
{
	float dy = 0 - (segs[0].ddy * getPercentage());
	float y = 0.f;

	for (int i = 0; i < segs.size(); i++)
	{
		segs[i].dy = y;
		dy += segs[i].ddy;
		y += dy;
	}
}

void sRoad::project(float camX, float camY, float camZ, int i)
{
	float xCam, yCam, zCam, xProj, yProj, camMultiplier, xScreen, yScreen, distance;

	xCam = segs[i].x - segs[i].dx - camX;
	yCam = segs[i].y - segs[i].dy - camY;
	zCam = segs[i].z1 - camZ;

	camMultiplier = THE_D / zCam;
	segs[i].scale = camMultiplier;

	xProj = xCam * camMultiplier;
	yProj = yCam * camMultiplier;

	xScreen = HALF_WIDTH + (HALF_WIDTH * xProj);
	yScreen = HALF_HEIGHT - (HALF_HEIGHT * yProj);

	if (grassHeight > yScreen)
	{
		grassHeight = yScreen;
		grassRender = i;
	}

	segs[i].road.setPosition(sf::Vector2f(xScreen, yScreen));
	segs[i].road.setScale(sf::Vector2f(camMultiplier, camMultiplier));
}

void sRoad::addSegment(float x, float y, float ddx, float ddy, float nearBackX, float farBackX, float backY)
{
	if (segs.size() == 0)
		tempSeg.z1 = SEGMENT_THRESHOLD;
	else
		tempSeg.z1 = segs[segs.size() - 1].z2;
	
	tempSeg.z2 = tempSeg.z1 + SEGMENT_LENGTH;
	tempSeg.x = x;
	tempSeg.y = y;
	tempSeg.ddx = ddx;
	tempSeg.ddy = ddy;
	tempSeg.nearBackgroundRotate = nearBackX;
	tempSeg.farBackgroundRotate = farBackX;
	tempSeg.backgroundY = backY;
	
	segs.push_back(tempSeg);
}

void sRoad::addRepeatSegment()
{
	if (segs.size() == 0)
		tempSeg.z1 = 0.0;
	else
		tempSeg.z1 = segs[segs.size() - 1].z2;

	tempSeg.z2 = tempSeg.z1 + SEGMENT_LENGTH;

	segs.push_back(tempSeg);
}

void sRoad::addSegmentAtBegin(float x, float y, float z1)
{
	tempSeg.z1 = z1;
	tempSeg.z2 = tempSeg.z1 + SEGMENT_LENGTH;
	tempSeg.x = x;
	tempSeg.y = y;
	tempSeg.ddx = 0;
	tempSeg.ddy = 0;
	tempSeg.road.setTexture(roadSpriteSheet);
	tempSeg.road.setTextureRect(sf::IntRect(0, 0, 400, 50));
	tempSeg.road.setOrigin(sf::Vector2f(200, 0));
	segs.insert(segs.begin(), tempSeg);
}

void sRoad::moveSegs(float speed)
{
	int i = 0;
	while (i < segs.size())
	{
		segs[i].z1 -= speed;
		segs[i].z2 -= speed;
		i++;
	}
}

void sRoad::setRoadType(int choice)
{
	switch (choice)
	{
	case 1:
		tempSeg.road.setTextureRect(sf::IntRect(0, 0, 400, 50));
		break;
	case 2:
		tempSeg.road.setTextureRect(sf::IntRect(0, 50, 400, 50));
		break;
	case 4:
		tempSeg.road.setTextureRect(sf::IntRect(400, 0, 400, 50));
		break;
	}
}

void sRoad::animateGrass()
{
	grassAnimation += 80;
	if (grassAnimation >= 1280)
		grassAnimation = 0;
}

void sRoad::eraseFirstSegment()
{
	segs.erase(segs.begin());
}

float sRoad::getPercentage()
{
	if (segs.size() > 0)
		return (SEGMENT_THRESHOLD - segs[0].z1) * SEGMENT_LENGTH_ADJUSTER;
	else
		return 0.0f;
}

sRoadSegment sRoad::operator[](int i)
{
	return segs[i];
}

sf::Vector2f sRoad::getXY(int i)
{
	if (i >= 0 && i < segs.size())
		return segs[i].road.getPosition();
	else
		return sf::Vector2f(0, 0);
}

int sRoad::size()
{
	return segs.size();
}

bool sRoad::segOverThreshold()
{
	if (segs.size() > 0 && segs[0].z2 < SEGMENT_THRESHOLD)
		return true;
	else
		return false;
}
