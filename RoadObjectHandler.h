#include "Globals.h"
#include "FileLoader.h"

#ifndef ROADOBJECTHANDLER_H
#define ROADOBJECTHANDLER_H
class RoadObjectHandler
{
public:
	RoadObjectHandler();
	~RoadObjectHandler();

	void render(sf::RenderWindow &window, int i);

	void loadFromFile(FileLoader &file, std::string fileName, int size);

	void placeObjects(int i, sf::Vector2f coords, float scale);
	void removeFirstSet();

private:

	std::vector <ObjectSet> objectSets;
};
#endif // !ROADOBJECTHANDLER_H

