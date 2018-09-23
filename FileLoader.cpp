#include "stdafx.h"
#include "FileLoader.h"


FileLoader::FileLoader()
{
	texture.loadFromFile("res/sprites/roadObjects.png");

	happyFace.object.setTexture(texture);
	happyFace.object.setTextureRect(sf::IntRect(17, 17, 143, 171));
	happyFace.object.setOrigin(sf::Vector2f(143 / 2,  171));

	angryFace.object.setTexture(texture);
	angryFace.object.setTextureRect(sf::IntRect(204, 16, 142, 169));
	angryFace.object.setOrigin(sf::Vector2f(142 / 2, 169));

	dukeFace.object.setTexture(texture);
	dukeFace.object.setTextureRect(sf::IntRect(370, 35, 137, 132));
	dukeFace.object.setOrigin(sf::Vector2f(137 / 2, 132));

	backgroundY = 0.f;
	farBackgroundPosition = 0.f;
	nearBackgroundPosition = 0.f;
}


FileLoader::~FileLoader()
{
}

void FileLoader::openRoadFile(std::string fileName)
{
	roadData.open(fileName);
}

void FileLoader::openObjectFile(std::string filename)
{
	objectData.open(filename);
}

void FileLoader::loadRoadData(CourseSegment & segment)
{
	RoadInfo tempSeg;
	char fuck;
	float x, y, ddx, ddy;
	int position;
	std::vector <float> flots;

	roadData >> segment.length;
	roadData >> segment.roadType;
	roadData >> segment.grassType;

	for (int i = 0; i < segment.length; i++)
	{
		segment.roadSegs.push_back(tempSeg);
	}

		roadData >> fuck;

		while (fuck != 'x')
		{
			roadData.unget();
			roadData >> ddx;
			roadData >> position;
			roadData >> fuck;
			flots.push_back(ddx);
			if (flots.size() > 1)
				interpolate(flots, flots.size() - 2, position);
		}
		extend(flots, flots.size() - 1, segment.length);
		for (int i = 0; i < segment.length; i++)
		{
			segment.roadSegs[i].ddx = flots[0];
			flots.erase(flots.begin());
		}

		roadData >> fuck;
		while (fuck != 'x')
		{
			roadData.unget();
			roadData >> ddy;
			roadData >> position;
			roadData >> fuck;
			flots.push_back(ddy);
			if (flots.size() > 1)
				interpolate(flots, flots.size() - 2, position);
		}
		extend(flots, flots.size() - 1, segment.length);

		for (int i = 0; i < segment.length; i++)
		{
			segment.roadSegs[i].ddy = flots[0];
			flots.erase(flots.begin());
		}

		roadData >> fuck;
		while (fuck != 'x')
		{
			roadData.unget();
			roadData >> x;
			roadData >> position;
			roadData >> fuck;
			flots.push_back(x);
			if (flots.size() > 1)
				interpolate(flots, flots.size() - 2, position);
		}
		extend(flots, flots.size() - 1, segment.length);

		for (int i = 0; i < segment.length; i++)
		{
			segment.roadSegs[i].x = flots[0];
			flots.erase(flots.begin());
		}
		
		roadData >> fuck;
		while (fuck != 'x')
		{
			roadData.unget();
			roadData >> y;
			roadData >> position;
			roadData >> fuck;
			flots.push_back(y);
			if (flots.size() > 1)
				interpolate(flots, flots.size() - 2, position);
		}
		extend(flots, flots.size() - 1, segment.length);


		for (int i = 0; i < segment.length; i++)
		{
			segment.roadSegs[i].y = flots[0];
			flots.erase(flots.begin());
		}

		for (int j = 0; j < segment.length; j++)
		{
			farBackgroundPosition -= segment.roadSegs[j].ddx * FAR_BACKGROUND_ROTATE;
			nearBackgroundPosition -= segment.roadSegs[j].ddx * NEAR_BACKGROUND_ROTATE;
			backgroundY += segment.roadSegs[j].ddy * BACKGROUND_Y_ROTATE;
			segment.roadSegs[j].farBackgroundRotate = farBackgroundPosition;
			segment.roadSegs[j].nearBackgroundRotate = nearBackgroundPosition;
			segment.roadSegs[j].backgroundY = backgroundY;
		}

		roadData >> fuck;
		if(!roadData.eof())
		roadData.unget();
}

void FileLoader::loadObjectData(std::vector <ObjectSet> & sets, int size)
{
	for (int i = 0; i < size; i++)
	{
		sets.push_back(tempSet);
	}
	int i, loop, id, location;
	float dist;

	objectData >> id;

	while (!objectData.eof())
	{
		i = 0;
		objectData >> loop;
		while (i < loop)
		{
			objectData >> location;
			objectData >> dist;

			switch (id)
			{
			case 1:
				happyFace.distFromCenter = dist;
				sets[location].objects.push_back(happyFace);
				break;
			case 2:
				angryFace.distFromCenter = dist;
				sets[location].objects.push_back(angryFace);
				break;
			case 3:
				dukeFace.distFromCenter = dist;
				sets[location].objects.push_back(dukeFace);
				break;
			}

			i++;
		}

		objectData >> id;
		i = 0;
	}
}

void FileLoader::interpolate(std::vector<float>& floats, int beginning, int end)
{
	int elementsBetween;
	int i = 1;
	float difference;
	float tempFloat;

	elementsBetween = end - beginning;
	difference = floats[beginning + 1] - floats[beginning];
	while (i < elementsBetween)
	{
		tempFloat = floats[beginning] + (difference * (float(i) / float(elementsBetween)));
		floats.insert(floats.begin() + beginning + i, tempFloat);
		i++;
	}
}

void FileLoader::extend(std::vector<float>& floats, int beginning, int end)
{
	int elementsBetween;
	int i = 1;
	float tempFloat;

	elementsBetween = end - beginning;
	while (i < elementsBetween)
	{
		floats.push_back(floats[beginning]);
		i++;
	}
}

void FileLoader::resetBackgroundVars()
{
	backgroundY = 0.f;
	farBackgroundPosition = 0.f;
	nearBackgroundPosition = 0.f;
}

bool FileLoader::eof()
{
	return roadData.eof();
}
