#include "Globals.h"
#ifndef SROAD_H
#define ROAD_H

class sRoad
{
public:
	sRoad();
	~sRoad();

	void update(float speed, float delta);
	void render(sf::RenderWindow &window, int i);
	void debugRender(sf::RenderWindow &window);

	void calculateDX();
	void calculateDY();
	void project(float camX, float camY, float camZ, int i);
	void addSegment(float x, float y, float ddx, float ddy, float nearBackX, float farBackX, float backY);
	void addRepeatSegment();
	void addSegmentAtBegin(float x, float y, float z1);
	void moveSegs(float speed);

	void setRoadType(int choice);/*1-3 for concrete
								4-6 for sand/dirt
								*/
	void animateGrass();

	void eraseFirstSegment();

	float getPercentage();

	sRoadSegment operator [](int i);

	sf::Vector2f getXY(int i);

	int size();

	bool segOverThreshold();

private:
	sf::Texture roadSpriteSheet;
	sf::RectangleShape grass;

	std::vector<sRoadSegment> segs;
	sRoadSegment tempSeg;
	int grassAnimation;

	float grassHeight;
	int grassRender;
};

#endif