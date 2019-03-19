#pragma once
#include <SFML\Graphics.hpp>

class Slider : public sf::RectangleShape {

public:

	Slider();
	~Slider() { delete sliderSprite; delete sliderTexture; }

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void updatePosition(const sf::Vector2f &position);

	double getParameter() const { return parameter; }

private:

	const int sizeX = 1000;
	const int sizeY = 100;
	double parameter = 0.0;
	sf::VertexArray line = sf::VertexArray(sf::Lines, 2);
	sf::Texture *sliderTexture = new sf::Texture();
	sf::Sprite *sliderSprite = new sf::Sprite();

};