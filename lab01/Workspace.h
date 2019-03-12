#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Workspace {

public:
	Workspace(sf::RenderWindow *sourceWindow) : window(sourceWindow) {}
	~Workspace() { this->flush(); }

	void addTemporary(sf::Drawable *figure) { pictures.push_back(figure); pictures.pop_back();  }
	void addDefinitely(sf::Drawable *figure) { pictures.push_back(figure); }

	void saveToFile(std::string file);
	void openFile(std::string file);

	void draw() {
		for (auto &shape : pictures)
			window->draw(*shape);
	}

	void flush() {
		for (auto & shape : pictures)
			delete shape;
		pictures.clear();
	}

private:

	sf::RenderWindow *window;
	std::vector<sf::Drawable *> pictures;
	sf::Texture fileTexture;
};