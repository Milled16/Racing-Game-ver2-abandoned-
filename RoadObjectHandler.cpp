#include "stdafx.h"
#include "RoadObjectHandler.h"


RoadObjectHandler::RoadObjectHandler()
{
	
}


RoadObjectHandler::~RoadObjectHandler()
{
}

void RoadObjectHandler::render(sf::RenderWindow & window, int i)
{
	int j = 0;
	if (i < objectSets.size() && i >= 0)
	{
		while (j < objectSets[i].objects.size())
		{
			window.draw(objectSets[i].objects[j].object);
			j++;
		}
	}
}

void RoadObjectHandler::loadFromFile(FileLoader &file, std::string fileName, int size)
{
	file.openObjectFile(fileName);
	file.loadObjectData(objectSets, size);
}

void RoadObjectHandler::placeObjects(int i, sf::Vector2f coords, float scale)
{
	int j = 0;
	if (i >= 0 && i < objectSets.size())
	{
		while (j < objectSets[i].objects.size())
		{
			objectSets[i].objects[j].object.setPosition(sf::Vector2f(coords.x + objectSets[i].objects[j].distFromCenter * scale, coords.y));
			objectSets[i].objects[j].object.setScale(sf::Vector2f(scale, scale));
			j++;
		}
	}
}

void RoadObjectHandler::removeFirstSet()
{
	if (objectSets.size() > 0)
		objectSets.erase(objectSets.begin());
}
