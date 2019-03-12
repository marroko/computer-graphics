#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Workspace.h"

constexpr double PI = 3.141592653589793238463;

void drawRectangle(Menu &menu, sf::RenderWindow &window, Workspace &workspace, char type) {

	sf::RectangleShape *rectangle = new sf::RectangleShape(menu.mousePosition - menu.clickPosition);

	rectangle->setPosition(menu.clickPosition);
	rectangle->setOutlineColor(menu.getDrawColor());
	rectangle->setOutlineThickness(1);

	if(type == 'r') // R - opcja normalnego prostokata
		rectangle->setFillColor(sf::Color::Transparent);
	else 
		rectangle->setFillColor(menu.getFillColor()); // wypelniony prostokat

	window.draw(*rectangle);

	if (menu.mousePressed) {

		workspace.addTemporary(rectangle);
		delete rectangle;
	}
	else workspace.addDefinitely(rectangle);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	Menu menu;
	Workspace workspace(&window);

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		using namespace sf;

		while (window.pollEvent(event))
		{
			switch (event.type) {

			case Event::Closed: { window.close(); break; }

			case Event::KeyPressed: {

				menu.keyPressed = true;
				menu.mousePressed = true;

				switch (event.key.code) {

				case Keyboard::F:
					menu.setCurrentKey('F'); break;
				case Keyboard::B:
					menu.setCurrentKey('B'); break;
				case Keyboard::L:
					menu.setCurrentKey('L'); break;
				case Keyboard::R:
					menu.setCurrentKey('R'); break;
				case Keyboard::A:
					menu.setCurrentKey('A'); break;
				case Keyboard::C:
					menu.setCurrentKey('C'); break;
				case Keyboard::W:
					menu.setCurrentKey('W'); break;
				case Keyboard::O:
					menu.setCurrentKey('O'); break;
				case Keyboard::Space: { // nowa funkcjonalnosc - czyszczenie obrazu

					menu.setCurrentKey('S');
					workspace.flush();
					workspace.openFile("black.png");
					break;
				}
				case Keyboard::Escape:
					window.close(); break;

				default: break;
				}
				break;
			}

			case Event::MouseButtonPressed: {

				menu.clickPosition = Vector2f(event.mouseButton.x, event.mouseButton.y);

				if (menu.clickPosition.x < 766 && menu.clickPosition.y < 61)
					menu.setTmpClick(Menu::whereClicked::Palette);
				else if (menu.clickPosition.y > 60 && menu.clickPosition.y < 598)
					menu.setTmpClick(Menu::whereClicked::Workspace);
				else
					menu.setTmpClick(Menu::whereClicked::Nowhere);

				break;
			}
			case Event::MouseButtonReleased: {
				menu.mousePressed = false;
				break;
			}
			case Event::MouseMoved: {
				menu.mousePosition = Vector2f(event.mouseMove.x, event.mouseMove.y);
				break;
			}

			default: break;
			}
		}

		workspace.draw();

		if (menu.keyPressed) {

			if (menu.getTmpClick() == Menu::whereClicked::Palette) {

				switch (menu.getCurrentKey()) {

				case static_cast<wchar_t>('F') : {

					Color colour = menu.pickColor();
					menu.setDrawColor(colour);
					break;
				}
				case static_cast<wchar_t>('B') : {

					Color colour = menu.pickColor();
					menu.setFillColor(colour);
					break;
				}
				default: break;
				}
				menu.setTmpClick(Menu::whereClicked::Nowhere);
			}
			else if (menu.getTmpClick() == Menu::whereClicked::Workspace) {

				switch (menu.getCurrentKey()) {

				case static_cast<wchar_t>('L') : {

					VertexArray *line = new VertexArray(Lines, 2);
					(*line)[0] = Vertex(menu.clickPosition, menu.getDrawColor());
					(*line)[1] = Vertex(menu.mousePosition, menu.getDrawColor());
					window.draw(*line);

					if (menu.mousePressed) {

						workspace.addTemporary(line);
						delete line;
					}
					else workspace.addDefinitely(line);

					break;
				}
				case static_cast<wchar_t>('R') : {

					drawRectangle(menu, window, workspace, 'r');
					break;
				}
				case static_cast<wchar_t>('A') : {

					drawRectangle(menu, window, workspace, 'a');
					break;
				}
				case static_cast<wchar_t>('C') : {

					CircleShape *circle = new CircleShape();

					double distanceX = menu.clickPosition.x - menu.mousePosition.x;
					double distanceY = menu.clickPosition.y - menu.mousePosition.y;

					double r = sqrt(pow(distanceX, 2) + pow(distanceY, 2)) / 2.5;
					double rotAngle = atan2(-distanceY, -distanceX) * (180 / PI) - 45;
					circle->setRadius(r);
					circle->setPosition(menu.clickPosition);
					circle->rotate(rotAngle);

					circle->setOutlineColor(menu.getDrawColor());
					circle->setOutlineThickness(1);
					circle->setFillColor(Color::Transparent);

					window.draw(*circle);
					if (menu.mousePressed) {

						workspace.addTemporary(circle);
						delete circle;
					}
					else workspace.addDefinitely(circle);

					break;
				}

				default: break;
				}

				if (!menu.mousePressed) {

					menu.mousePressed = true;
					menu.setTmpClick(Menu::whereClicked::Nowhere);
				}
			}
			switch (menu.getCurrentKey()) {

			case static_cast<wchar_t>('W') : {

				workspace.saveToFile("workspace.png");
				menu.keyPressed = false;
				break;
			}
			case static_cast<wchar_t>('O') : {

				workspace.openFile("workspace.png");
				menu.keyPressed = false;
				break;
			}
			default: break;
			}
		}

	window.draw(menu);
	window.display();
	}

	return 0;
}