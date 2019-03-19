#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>
#include <string>

class ColorCircle : public sf::CircleShape {

public:

	static constexpr double M_PI = 3.14159265358979323846;
	static constexpr double M_PI3 = M_PI / 3;
	static constexpr double M2_PI3 = 2*M_PI / 3;
	static constexpr double M4_PI3 = 4*M_PI / 3;
	static constexpr double M5_PI3 = 5*M_PI / 3;
	static constexpr double M2_PI = 2*M_PI;

	ColorCircle(std::string info);
	virtual ~ColorCircle();

	virtual sf::Color pickColor(const double alpha, const double distance) const = 0;
	virtual void updateComponentInfo() = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void makeTexture();
	void updateCircle(double compValue);
	void prepareAngleRadius();

protected:

	const int radius = 180;
	double componentValue = 0.0;
	double **anglesArray = new double*[360];
	double **radiusArray = new double*[360];

	sf::Texture *interior;
	sf::Sprite *interiorSprite;
	sf::Font font;
	sf::Text componentInfo;
	sf::Uint8 *colors;
	const std::string componentInfoBeginning;

};
