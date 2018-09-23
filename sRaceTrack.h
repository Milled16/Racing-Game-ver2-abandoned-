#include "sRoad.h"
#include "FileLoader.h"
#include "RoadObjectHandler.h"

#ifndef SRACETRACK_H
#define SRACETRACK_H
class sRaceTrack
{
public:
	sRaceTrack();
	~sRaceTrack();

	void process(bool leftPressed, bool rightPressed, bool upPressed, bool downPressed);
	void update(float delta);
	void render(sf::RenderWindow &window);

	void loadRoadData(std::string fileName);
	void projectRoad();
	void projectBackground();

	float clamp(float num, float min, float max);

private:
	FileLoader file;

	sRoad mainRoad;

	RoadObjectHandler objectHandler;
	//RiderHandler riderHandler;

	BackGround bg;
	float bgNearX, bgY, bgFarX;

	sf::Texture nearBackgroundTexture;
	sf::Texture farBackgroundTexture;

	TrackState state;

	sf::Sprite mad;
	sf::Texture madText;

	sf::RectangleShape eveningSky;

	std::vector<CourseSegment> mainCourse;

	int currentBackground;
	int numOfBackgrounds;

	float farBackTextY[10];
	float farBackTextHeight[10];

	float nearBackTextY[10];
	float nearBackTextHeight[10];

	CourseSegment tempSeg;
	int currentSegment;

	float percentage;
	float lastFarbackX, lastNearbackX, lastBackY;

	float madX, madZ, madY;

	/* these are for where the camera is*/
	float camX = 0;
	float camY = 0.8f;
	float camZ = 0;

	float accelAmount;
	float brakeAmount;
	float turnAmount;
	float speed;
	float animationTime;

	int numOfCourses;
	int numOfForks;
};

#endif