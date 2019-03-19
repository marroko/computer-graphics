#include "Slider.h"

Slider::Slider() {

	sf::Uint8 *colors = new sf::Uint8[4 * sizeX * sizeY];

	for (int x = 0; x < sizeX; ++x) {

		for (int y = 0; y < sizeY; ++y) {

		if (x==0 || x==1 || y==0 || y==1 || x == sizeX - 2 || x==sizeX-1 || y==sizeY-2 || y==sizeY-1) {

				colors[4 * (y * sizeX + x) + 0] = 204;
				colors[4 * (y * sizeX + x) + 1] = 0;
				colors[4 * (y * sizeX + x) + 2] = 0;
				colors[4 * (y * sizeX + x) + 3] = 250;
			}
			else {
				colors[4 * (y * sizeX + x) + 0] = x * 255 / sizeX;
				colors[4 * (y * sizeX + x) + 1] = x * 255 / sizeX;
				colors[4 * (y * sizeX + x) + 2] = x * 255 / sizeX;
				colors[4 * (y * sizeX + x) + 3] = 250;
			}
		}
	}
	sliderTexture->create(sizeX, sizeY);
	sliderTexture->update(colors);

	line[0] = sf::Vertex(sf::Vector2f(sizeX / 2, -15), sf::Color::Black);
	line[1] = sf::Vertex(sf::Vector2f(sizeX / 2, sizeY + 15), sf::Color::Black);
	sliderSprite->setTexture(*sliderTexture);

	delete [] colors;
}

void Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	
	states.transform *= getTransform();
	target.draw(line, states);
	target.draw(*sliderSprite, states);
}

void Slider::updatePosition(const sf::Vector2f &position) {

	const sf::Vector2f sliderPosition = getPosition();

	if ((sliderPosition.x <= position.x && sliderPosition.x + sizeX >= position.x)
		&& (sliderPosition.y <= position.y && sliderPosition.y + sizeY >= position.y)) {

		line[0].position.x = line[1].position.x = position.x - sliderPosition.x;
		parameter = (position.x - sliderPosition.x) / sizeX;
	}
}