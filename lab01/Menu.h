#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable {

public:

	Menu();
	~Menu();
	enum whereClicked { Palette, Workspace, Nowhere };

	void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Color pickColor();

	void setDrawColor(const sf::Color &c) { drawingColor = c; 
											drawColorSquare->setFillColor(c); }
	void setFillColor(const sf::Color &c) { fillingColor = c; 
											fillColorSquare->setFillColor(c); }
	sf::Color getDrawColor() { return drawingColor; }
	sf::Color getFillColor() { return fillingColor; }

	void setTmpClick(whereClicked here) { tmpClick = here; }
	void setCurrentKey(wchar_t letter) { currentKey = letter; }
	whereClicked getTmpClick() { return tmpClick; }
	wchar_t getCurrentKey() { return currentKey; }

	sf::Vector2f mousePosition;
	sf::Vector2f clickPosition;
	bool mousePressed = false;
	bool keyPressed = false;

private:

	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);

	whereClicked tmpClick = Nowhere;

	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;
	sf::Texture *colorsTexture;
	sf::Texture *tmp;
	sf::Sprite *colorsSprite;
	sf::Sprite *menuToolbar;
	sf::Uint8 *colorsPixels;
	const unsigned int colorsSizeX = 765;
	const unsigned int colorsSizeY = 60;

	wchar_t currentKey = '\0';
	sf::RectangleShape *drawColorSquare = nullptr;
	sf::RectangleShape *fillColorSquare = nullptr;
	sf::Color drawingColor;
	sf::Color fillingColor;
};