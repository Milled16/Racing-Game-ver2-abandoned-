#include "stdafx.h"
#include "SpriteText.h"


SpriteText::SpriteText()
{
}


SpriteText::~SpriteText()
{
}

void SpriteText::render(sf::RenderWindow & window)
{
	for (int i = 0; i < text.size(); i++)
	{
		window.draw(text[i]);
	}
}

void SpriteText::setTexture(sf::Texture * texture)
{
	this->texture = texture;
	tempSprite.setTexture(*texture);
}

void SpriteText::setText(int shit, sf::Vector2f position)
{
	xny = position;
	text.clear();
	int chara;
	width = 0;
	while (shit > 0)
	{
		chara = shit % 10;
		text.insert(text.begin(), tempSprite);
		text[0].setColor(color);

		intSwitch(chara);

		shit /= 10;
	}
	
	setPosition(position);
}

void SpriteText::setText(int shit)
{
	text.clear();
	int chara;
	width = 0;
	while (shit > 0)
	{
		chara = shit % 10;
		text.insert(text.begin(), tempSprite);
		text[0].setColor(color);

		intSwitch(chara);

		shit /= 10;
	}
	
	setPosition(xny);
}

void SpriteText::intSwitch(int i)
{
	switch (i)
	{
	case 0:
		text[0].setTextureRect(sf::IntRect(71, 0, 7, 10));
		break;
	case 1:
		text[0].setTextureRect(sf::IntRect(0, 0, 6, 10));
		break;
	case 2:
		text[0].setTextureRect(sf::IntRect(7, 0, 7, 10));
		break;
	case 3:
		text[0].setTextureRect(sf::IntRect(15, 0, 6, 10));
		break;
	case 4:
		text[0].setTextureRect(sf::IntRect(22, 0, 7, 10));
		break;
	case 5:
		text[0].setTextureRect(sf::IntRect(30, 0, 8, 10));
		break;
	case 6:
		text[0].setTextureRect(sf::IntRect(39, 0, 7, 10));
		break;
	case 7:
		text[0].setTextureRect(sf::IntRect(47, 0, 8, 10));
		break;
	case 8:
		text[0].setTextureRect(sf::IntRect(56, 0, 7, 10));
		break;
	case 9:
		text[0].setTextureRect(sf::IntRect(64, 0, 6, 10));
		break;
	}
}

void SpriteText::setText(std::string shit, sf::Vector2f position)
{
	text.clear();
	xny = position;
	char chara;
	int i = 0;

	chara = shit[i];
	while (chara != '\0')
	{
		text.push_back(tempSprite);
		text[i].setColor(color);
		charSwitch(chara, i);
		
		i++;
		chara = shit[i];
	}
	
	setPosition(position);
}

void SpriteText::setText(std::string shit)
{
	text.clear();
	char chara;
	int i = 0;

	chara = shit[i];
	while (chara != '\0')
	{
		text.push_back(tempSprite);
		text[i].setColor(color);

		charSwitch(chara, i);

		i++;
		chara = shit[i];
	}

	setPosition(xny);
}

void SpriteText::charSwitch(char chara, int i)
{
	switch (chara)
	{
	case 'a':
	case 'A':
		text[i].setTextureRect(sf::IntRect(79, 0, 10, 10));
		break;
	case 'b':
	case 'B':
		text[i].setTextureRect(sf::IntRect(90, 0, 6, 10));
		break;
	case 'c':
	case 'C':
		text[i].setTextureRect(sf::IntRect(97, 0, 8, 10));
		break;
	case 'd':
	case 'D':
		text[i].setTextureRect(sf::IntRect(106, 0, 9, 10));
		break;
	case 'e':
	case 'E':
		text[i].setTextureRect(sf::IntRect(116, 0, 6, 10));
		break;
	case 'f':
	case 'F':
		text[i].setTextureRect(sf::IntRect(123, 0, 6, 10));
		break;
	case 'g':
	case 'G':
		text[i].setTextureRect(sf::IntRect(130, 0, 9, 10));
		break;
	case 'h':
	case 'H':
		text[i].setTextureRect(sf::IntRect(140, 0, 8, 10));
		break;
	case 'i':
	case 'I':
		text[i].setTextureRect(sf::IntRect(149, 0, 8, 10));
		break;
	case 'j':
	case 'J':
		text[i].setTextureRect(sf::IntRect(158, 0, 10, 10));
		break;
	case 'k':
	case 'K':
		text[i].setTextureRect(sf::IntRect(169, 0, 7, 10));
		break;
	case 'l':
	case 'L':
		text[i].setTextureRect(sf::IntRect(177, 0, 7, 10));
		break;
	case 'm':
	case 'M':
		text[i].setTextureRect(sf::IntRect(185, 0, 8, 10));
		break;
	case 'n':
	case 'N':
		text[i].setTextureRect(sf::IntRect(194, 0, 8, 10));
		break;
	case 'o':
	case 'O':
		text[i].setTextureRect(sf::IntRect(203, 0, 10, 10));
		break;
	case 'p':
	case 'P':
		text[i].setTextureRect(sf::IntRect(214, 0, 8, 10));
		break;
	case 'q':
	case 'Q':
		text[i].setTextureRect(sf::IntRect(223, 0, 13, 10));
		break;
	case 'r':
	case 'R':
		text[i].setTextureRect(sf::IntRect(237, 0, 10, 10));
		break;
	case 's':
	case 'S':
		text[i].setTextureRect(sf::IntRect(248, 0, 8, 10));
		break;
	case 't':
	case 'T':
		text[i].setTextureRect(sf::IntRect(257, 0, 8, 10));
		break;
	case 'u':
	case 'U':
		text[i].setTextureRect(sf::IntRect(266, 0, 10, 10));
		break;
	case 'v':
	case 'V':
		text[i].setTextureRect(sf::IntRect(277, 0, 10, 10));
		break;
	case 'w':
	case 'W':
		text[i].setTextureRect(sf::IntRect(288, 0, 12, 10));
		break;
	case 'x':
	case 'X':
		text[i].setTextureRect(sf::IntRect(301, 0, 10, 10));
		break;
	case 'y':
	case 'Y':
		text[i].setTextureRect(sf::IntRect(312, 0, 8, 10));
		break;
	case 'z':
	case 'Z':
		text[i].setTextureRect(sf::IntRect(321, 0, 9, 10));
		break;
	case '0':
		text[i].setTextureRect(sf::IntRect(71, 0, 7, 10));
		break;
	case '1':
		text[i].setTextureRect(sf::IntRect(0, 0, 6, 10));
		break;
	case '2':
		text[i].setTextureRect(sf::IntRect(7, 0, 7, 10));
		break;
	case '3':
		text[i].setTextureRect(sf::IntRect(15, 0, 6, 10));
		break;
	case '4':
		text[i].setTextureRect(sf::IntRect(22, 0, 7, 10));
		break;
	case '5':
		text[i].setTextureRect(sf::IntRect(30, 0, 8, 10));
		break;
	case '6':
		text[i].setTextureRect(sf::IntRect(39, 0, 7, 10));
		break;
	case '7':
		text[i].setTextureRect(sf::IntRect(47, 0, 8, 10));
		break;
	case '8':
		text[i].setTextureRect(sf::IntRect(56, 0, 7, 10));
		break;
	case '9':
		text[i].setTextureRect(sf::IntRect(64, 0, 6, 10));
		break;
	default:
		text[i].setTextureRect(sf::IntRect(331, 0, 10, 5));
		break;
	}
}

void SpriteText::setPosition(sf::Vector2f position)
{
	for (int i = 0; i < text.size(); i++)
	{
		text[i].setPosition(position);
		position.x += text[i].getTextureRect().width;
		width += text[i].getTextureRect().width;
	}
}

void SpriteText::setXNY(sf::Vector2f xny)
{
	this->xny = xny;
	setPosition(xny);
}

void SpriteText::setColor(sf::Color color)
{
	this->color = color;
	for (int i = 0; i < text.size(); i++)
	{
		text[i].setColor(color);
	}
}

int SpriteText::getWidth()
{
	return width;
}
