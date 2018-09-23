#include "stdafx.h"
#include "RiderHandler.h"


RiderHandler::RiderHandler()
{
	debugTexture.loadFromFile("res/sprites/text.png");
	debug.setTexture(&debugTexture);
	debug.setColor(sf::Color::Red);

	riderSheet.loadFromFile("res/sprites/riders.png");
	tempRider.rider.setTexture(riderSheet);
	
	for (int i = 0; i < 10; i++)
	{
		riders.push_back(tempRider);
		riders[i].rider.setTextureRect(sf::IntRect(0, 0, 51, 91));
		riders[i].rider.setOrigin(sf::Vector2f(26, 91));
		riders[i].rider.setPosition(sf::Vector2f(SEGMENT_THRESHOLD + 51 * i, YRES));
		riders[i].z = .5 + 1.f * float(i);
		if (i % 2 == 0)
			riders[i].distFromCenter = 100;
		else
			riders[i].distFromCenter = -100;
	}
}


RiderHandler::~RiderHandler()
{
}

void RiderHandler::update(float delta, float speed)
{
	float adjustedSpeed = speed * delta;
	float adjustedEnemySpeed = ENEMY_SPEED * delta;

	for (int i = 0; i < riders.size(); i++)
	{
		riders[i].z += adjustedEnemySpeed - adjustedSpeed;
	}

	int i = riders.size() - 1;
	while (i >= 0 && riders[i].z >= ROAD_LENGTH)
	{
		i--;
	}
	
	riderRenderCounter = i;
	riderPlacerCounter = i;
	debug.setText(i, sf::Vector2f(0, 20));

	while (i >= 0 && riders[i].z > 0.f)
	{
		riders[i].scale = THE_D / riders[i].z;
		riders[i].rider.setScale(sf::Vector2f(riders[i].scale, riders[i].scale));
		i--;
	}
}

void RiderHandler::render(sf::RenderWindow & window, float z1, float z2)
{
	while (riderRenderCounter >= 0 && riders[riderRenderCounter].z > z2)
		riderRenderCounter--;

	while (riderRenderCounter >= 0 && riders[riderRenderCounter].z > z1 && riders[riderRenderCounter].z <= z2)
	{
		window.draw(riders[riderRenderCounter].rider);
		riderRenderCounter--;
	}
}

void RiderHandler::debugRender(sf::RenderWindow & window)
{
	debug.render(window);
}

void RiderHandler::placeObjects(sRoadSegment firstSeg, sRoadSegment lastSeg)
{
	float percentage, xScreen, yScreen;
	while (riderPlacerCounter >= 0 && riders[riderPlacerCounter].z >= firstSeg.z1 && riders[riderPlacerCounter].z < lastSeg.z1)
	{
		percentage = (riders[riderPlacerCounter].z - firstSeg.z1) * SEGMENT_LENGTH_ADJUSTER;
		xScreen = (firstSeg.road.getPosition().x + (lastSeg.road.getPosition().x - firstSeg.road.getPosition().x) * percentage) + riders[riderPlacerCounter].distFromCenter * riders[riderPlacerCounter].rider.getScale().x;
		yScreen = firstSeg.road.getPosition().y + (lastSeg.road.getPosition().y - firstSeg.road.getPosition().y) * percentage;
		riders[riderPlacerCounter].rider.setPosition(sf::Vector2f(xScreen, yScreen));

		riderPlacerCounter--;
	}
}
