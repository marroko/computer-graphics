#include "Workspace.h"

void Workspace::saveToFile(std::string file) {

	sf::Texture texture;
	texture.create(window->getSize().x, window->getSize().y);
	texture.update(*window);

	sf::Image workspace;
	workspace.create(796, 536, sf::Color::Black);
	workspace.copy(texture.copyToImage(), 0, 0, sf::IntRect(2, 62, 796, 536)); // (2, 62) : 796x536
	workspace.saveToFile(file);
}

void Workspace::openFile(std::string file) {

	this->flush();
	window->clear(sf::Color::Black);

	fileTexture.loadFromFile(file);
	sf::Sprite *fileSprite = new sf::Sprite(fileTexture);

	this->addDefinitely(fileSprite);
}