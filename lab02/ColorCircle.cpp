#include "ColorCircle.h"

ColorCircle::ColorCircle(std::string info = "") : interior(new sf::Texture),
												  interiorSprite(new sf::Sprite),
											      colors(new sf::Uint8[16 * radius * radius]),
												  componentInfoBeginning(info) {
	this->setRadius(radius);

	font.loadFromFile("arial.ttf");
	componentInfo.setFont(font);
	componentInfo.setCharacterSize(25);
	componentInfo.setStyle(sf::Text::Bold);
	componentInfo.setFillColor(sf::Color::Black);
	componentInfo.setPosition(150.0, 360.0);

	interior->create(2 * radius, 2 * radius);
	prepareAngleRadius();
}

ColorCircle::~ColorCircle() {

	delete interior;
	delete interiorSprite;
	delete [] colors;

	for (int i = 0; i < 2*radius; i++) {

		delete[] radiusArray[i];
		delete[] anglesArray[i];
	}
	delete[] radiusArray;
	delete[] anglesArray;
}

void ColorCircle::makeTexture() {

	for (int x = 0; x < 2*radius; ++x) {

		for (int y = 0; y < 2*radius; ++y) {

			sf::Color c = pickColor(anglesArray[x][y], radiusArray[x][y]);

			if (radiusArray[x][y] <= radius) {

				colors[4 * (y * 2 * radius + x) + 0] = c.r;
				colors[4 * (y * 2 * radius + x) + 1] = c.g;
				colors[4 * (y * 2 * radius + x) + 2] = c.b;
				colors[4 * (y * 2 * radius + x) + 3] = 255;
			}
			else {
				for (int i = 0; i < 4; ++i)
					colors[4 * (y * 2 * radius + x) + i] = 0;
			}
		}
	}
	interior->update(colors);
	interiorSprite->setTexture(*interior);
}

void ColorCircle::updateCircle(double compValue) {

	if (fabs(componentValue - compValue) > 1e-6) {

		this->componentValue = compValue;
		this->updateComponentInfo();
		this->makeTexture();
		this->update();
	}
}

void ColorCircle::draw(sf::RenderTarget &target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(*interiorSprite, states);
	target.draw(componentInfo, states);
}

void ColorCircle::prepareAngleRadius() {

	double xx, yy;

	for (int i = 0; i < 2*radius; i++) {

		radiusArray[i] = new double[360];
		anglesArray[i] = new double[360];
	}

	for (int x = 0; x < 2 * radius; ++x) {

		for (int y = 0; y < 2 * radius; ++y) {

			xx = x - radius;
			yy = radius - y;

			anglesArray[x][y] = atan2(yy, xx);
			radiusArray[x][y] = sqrt(xx * xx + yy * yy);

			if (anglesArray[x][y] < 0.0)
				anglesArray[x][y] = M2_PI + fmod(anglesArray[x][y], M2_PI);
		}
	}
}