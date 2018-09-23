#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "steam/steam_api.h"
#include <iostream>
#include <cmath>
#include <vector>

#ifndef GLOBALS_H
#define GLOBALS_H

const float THE_D = .45f;
;
/* The time between updates */
const sf::Time UPDATE_TIME = sf::seconds(1.f / 120.f);
const sf::Time ANIMATION_TIME = sf::seconds(1.f / 12.f);

/*	X dimension of screen	*/
const int XRES = 320;

const float HALF_WIDTH = float(XRES) / 2.f;

/*	Y dimension of screen	*/
const int YRES = 240;

const float HALF_HEIGHT = float(YRES) / 2.f;

/* Fastest the player drives */
const float SPEED_LIMIT = 4.f;
const float BOOST_LIMIT = SPEED_LIMIT / 8.f;
const float ENEMY_SPEED = SPEED_LIMIT - (SPEED_LIMIT * .4);
const float SLOW_ENEMY_SPEED = SPEED_LIMIT - (SPEED_LIMIT * .5);
const float MAX_MOVE_SPEED = .5;

const float ACCELERATION = SPEED_LIMIT / 8.f;
const float BRAKE_SPEED = ACCELERATION * 2.f;

const float SEGMENT_LENGTH = .12;

const float SEGMENT_LENGTH_ADJUSTER = 1.f / SEGMENT_LENGTH;

const int MAX_SEGMENTS = 100;

const float ROAD_LENGTH = SEGMENT_LENGTH * MAX_SEGMENTS;

const float ROAD_GRAPHIC_WIDTH = 309.f;

const float SEGMENT_THRESHOLD = 0.f + SEGMENT_LENGTH;

struct sRoadSegment
{
	float z1, z2, ddx, ddy, dx, dy, x, y, scale;
	float nearBackgroundRotate;
	float farBackgroundRotate;
	float backgroundY;
	int roadID, leftGrassID, rightGrassID;
	sf::Sprite road;
};

struct RoadObject
{
	float distFromCenter;
	sf::RectangleShape hitBox;
	sf::Sprite object;
};

struct Rider
{
	float distFromCenter, z, scale;
	sf::RectangleShape hitBox;
	sf::Sprite rider;
};

struct BackGround
{
	sf::Sprite bgFar;
	sf::Sprite bgNear;
	sf::Sprite bottom;
	float nearScale, farScale;
};

const float NEAR_BACKGROUND_ROTATE = 400.f;
const float FAR_BACKGROUND_ROTATE = NEAR_BACKGROUND_ROTATE / 2.f;
const float BACKGROUND_Y_ROTATE = 100.f;

struct ObjectSet
{
	std::vector <RoadObject> objects;
};

struct RoadInfo
{
	float ddx;
	float ddy;
	float x;
	float y;
	float nearBackgroundRotate;
	float farBackgroundRotate;
	float backgroundY;
	int length, roadType, grassType;
};

struct CourseSegment
{
	std::vector<RoadInfo> roadSegs;

	/*std::vector<float> ddx;
	std::vector<float> ddy;
	std::vector<float> x;
	std::vector<float> y;
	std::vector<float> nearBackgroundRotate;
	std::vector<float> farBackgroundRotate;
	std::vector<float> backgroundY;*/
	int length, roadType, grassType;
};

enum TrackState
{
	Normal,
	TransitioningToNext
};

#endif // !GLOBALS_H