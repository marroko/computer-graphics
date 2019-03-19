#include <SFML/Window.hpp>
#include "ColorCircle.h"
#include "Circles.h"
#include "Slider.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1700, 768), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	sf::Event event;
	sf::Time time = sf::Time::Zero;
	unsigned int FPS = 0, frame_counter = 0;

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text fpsInfo;
	fpsInfo.setFont(font);
	fpsInfo.setCharacterSize(30);
	fpsInfo.setFillColor(sf::Color::Black);
	fpsInfo.setStyle(sf::Text::Bold);
	fpsInfo.setPosition(400, 680);

	constexpr int commonRadius = 180;
	constexpr int spacing = 30;

	CircleHSL hsl;
	hsl.setPosition(70, 60);
	CircleHSV hsv;
	hsv.setPosition(70 + spacing + commonRadius * 2, 60);
	CircleCMY cmy;
	cmy.setPosition(70 + spacing * 2 + commonRadius * 4, 60);
	CircleRGB rgb;
	rgb.setPosition(70 + spacing * 3 + commonRadius * 6, 60);

	Slider slider;
	slider.setPosition(400, 550);

	//inicjalizacja 
	clock.restart().asMilliseconds();

	window.setFramerateLimit(60);

	while (window.isOpen()) {

		window.clear(sf::Color(205,205,187));

		while (window.pollEvent(event)) {

			switch (event.type) {

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseMoved:
					slider.updatePosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
					break;

			default: break;
			}
		}

		double sliderPar = slider.getParameter();
		window.draw(slider);

		rgb.updateCircle(sliderPar);
		cmy.updateCircle(sliderPar);
		hsv.updateCircle(sliderPar);
		hsl.updateCircle(sliderPar);

		window.draw(rgb);
		window.draw(cmy);
		window.draw(hsv);
		window.draw(hsl);

		if (clock.getElapsedTime().asSeconds() >= 1.0f) {

			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;

		fpsInfo.setString("FPS: " + std::to_string(FPS) + "\nSlider: " + std::to_string(sliderPar));

		window.draw(fpsInfo);

		window.display();
	}
	return 0;
}