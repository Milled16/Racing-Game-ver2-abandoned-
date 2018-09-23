#include "Globals.h"
#include <fstream>

#ifndef FILELOADER_H
#define FILELOADER_H
class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	void openRoadFile(std::string fileName);
	void openObjectFile(std::string filename);

	void loadRoadData(CourseSegment & segment);
	void loadObjectData(std::vector <ObjectSet> & sets, int size);

	void interpolate(std::vector<float> &floats, int beginning, int end);
	void extend(std::vector<float> &floats, int beginning, int end);

	void resetBackgroundVars();
	bool eof();
private:
	std::ifstream roadData;
	std::ifstream objectData;

	sf::Texture texture;

	ObjectSet tempSet;

	float farBackgroundPosition, nearBackgroundPosition, backgroundY;
	std::vector <RoadObject> objects;

	RoadObject happyFace;
	RoadObject angryFace;
	RoadObject dukeFace;
};
#endif