#include "Menu.h"
#include "font.h"

inline void Menu::draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
{
	colorsPixels[4 * (y * colorsSizeX + x) + 0] = r;
	colorsPixels[4 * (y * colorsSizeX + x) + 1] = g;
	colorsPixels[4 * (y * colorsSizeX + x) + 2] = b;
	colorsPixels[4 * (y * colorsSizeX + x) + 3] = 255;
}

Menu::Menu() {

	font.loadFromMemory(font_data, font_data_size);
	text = new sf::Text;
	text->setFont(font);
	text->setCharacterSize(12);
	text->setFillColor(sf::Color::White);

	rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
	rectangle->setFillColor(sf::Color::Transparent);
	rectangle->setOutlineColor(sf::Color::White);
	rectangle->setOutlineThickness(1.0f);
	rectangle->setPosition(2, 62);

	unsigned int x, y;
	colorsPixels = new sf::Uint8[colorsSizeX * colorsSizeY * 4];
	for (x = 0; x<255; x++)
		for (y = 0; y < 30; y++)
		{
			draw_to_color_pixels(x, y, x, 255, 0);
			draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
			draw_to_color_pixels(x + 510, y, 255, 0, x);
			draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
			draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
			draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
		}

	colorsTexture = new sf::Texture();
	colorsTexture->create(colorsSizeX, colorsSizeY);
	colorsTexture->update(colorsPixels);

	colorsSprite = new sf::Sprite();
	colorsSprite->setTexture(*colorsTexture);
	colorsSprite->setPosition(1, 1);

	tmp = new sf::Texture();
	tmp->loadFromFile("black.png");

	menuToolbar = new sf::Sprite();
	menuToolbar->setPosition(2, 599);
	menuToolbar->setTexture(*tmp);

	drawColorSquare = new sf::RectangleShape(sf::Vector2f(30.0, 30.0));
	drawColorSquare->setFillColor(drawingColor);
	drawColorSquare->setOutlineColor(sf::Color::White);
	drawColorSquare->setOutlineThickness(1);
	drawColorSquare->setPosition(sf::Vector2f(colorsSizeX + 2, 1));

	fillColorSquare = new sf::RectangleShape(sf::Vector2f(30.0, 30.0));
	fillColorSquare->setFillColor(fillingColor);
	fillColorSquare->setOutlineColor(sf::Color::White);
	fillColorSquare->setOutlineThickness(1);
	fillColorSquare->setPosition(sf::Vector2f(colorsSizeX + 2, 1 + colorsSizeY/2));
}

Menu::~Menu() {

	delete text;
	delete rectangle;
	delete tmp;
	delete menuToolbar;
	delete colorsTexture;
	delete colorsSprite;
	delete [] colorsPixels;
	delete drawColorSquare;
	delete fillColorSquare;
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const
{
	text->setPosition(x, y);
	text->setString(str);
	target.draw(*text);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*menuToolbar);

	outtextxy(target, 5, 600, L"F - wybór koloru rysowania");
	outtextxy(target, 5, 615, L"B - wybór koloru wype³niania");
	outtextxy(target, 5, 630, L"L - rysowanie linii");

	outtextxy(target, 200, 600, L"R - rysowanie prostok¹ta");
	outtextxy(target, 200, 615, L"A - rysowanie wype³nionego prostok¹ta");
	outtextxy(target, 200, 630, L"C - rysowanie okrêgu");

	outtextxy(target, 470, 600, L"W - zapis do pliku");
	outtextxy(target, 470, 615, L"O - odczyt z pliku");
	outtextxy(target, 470, 630, L"esc - wyjœcie");

	outtextxy(target, 650, 605, L"Aktualne:");
	outtextxy(target, 600, 630, L"Space - czyszczenie ekranu");
	outtextxy(target, 720, 605, &currentKey);

	target.draw(*rectangle);
	target.draw(*colorsSprite);

	target.draw(*drawColorSquare);
	target.draw(*fillColorSquare);
}

sf::Color Menu::pickColor() {

	int x = static_cast<int>(mousePosition.x);
	int y = static_cast<int>(mousePosition.y);
	return sf::Color(colorsPixels[4 * (y * colorsSizeX + x) + 0],
					 colorsPixels[4 * (y * colorsSizeX + x) + 1],
					 colorsPixels[4 * (y * colorsSizeX + x) + 2]);
}