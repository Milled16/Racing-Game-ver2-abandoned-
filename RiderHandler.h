#include "Globals.h"
#include "SpriteText.h"

#ifndef RIDERHANDLER_H
#define RIDERHANDLER_H
class RiderHandler
{
public:
	RiderHandler();
	~RiderHandler();
	
	void update(float delta, float speed);
	void render(sf::RenderWindow &window, float z1, float z2);
	void debugRender(sf::RenderWindow &window);
	
	void placeObjects(sRoadSegment firstSeg, sRoadSegment lastSeg);
private:
	int riderRenderCounter, riderPlacerCounter;
	Rider tempRider;
	std::vector <Rider> riders;
	sf::Texture riderSheet;

	SpriteText debug;
	sf::Texture debugTexture;
};
#endif