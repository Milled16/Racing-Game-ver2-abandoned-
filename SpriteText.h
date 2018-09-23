#include "Globals.h"

#ifndef SPRITETEXT_H
#define SPRITETEXT_H
class SpriteText
{
public:
	SpriteText();
	~SpriteText();
	void render(sf::RenderWindow &window);

	void setTexture(sf::Texture *texture);

	void setText(int shit, sf::Vector2f position);
	void setText(int shit);
	void intSwitch(int i);

	void setText(std::string shit, sf::Vector2f position);
	void setText(std::string shit);
	void charSwitch(char chara, int i);

	void setPosition(sf::Vector2f position);
	void setXNY(sf::Vector2f xny);

	void setColor(sf::Color color);

	int getWidth();
private:
	sf::Texture *texture;
	std::vector <sf::Sprite> text;
	sf::Vector2f xny;
	sf::Sprite tempSprite;

	int width;
	sf::Color color;
};
#endif
