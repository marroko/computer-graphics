#pragma once
#include "ColorCircle.h"

class CircleHSL : public ColorCircle {

public:
	CircleHSL() : ColorCircle("HSL\nL = ") {

		makeTexture();
		updateComponentInfo();
	}
	virtual ~CircleHSL() = default;

	virtual sf::Color pickColor(const double alpha, const double distance) const;
	virtual void updateComponentInfo() {

		componentInfo.setString(componentInfoBeginning + std::to_string(componentValue));
	}
};

class CircleHSV : public ColorCircle {

public:

	CircleHSV() : ColorCircle("HSV\nV = ") {

		makeTexture();
		updateComponentInfo();
	}
	virtual ~CircleHSV() = default;

	virtual sf::Color pickColor(const double alpha, const double distance) const;
	virtual void updateComponentInfo() {

		componentInfo.setString(componentInfoBeginning + std::to_string(componentValue));
	}
};

class CircleCMY : public ColorCircle {

public:
	CircleCMY() : ColorCircle("CMY\nY = ") {

		makeTexture();
		updateComponentInfo();
	}
	virtual ~CircleCMY() = default;

	virtual sf::Color pickColor(const double alpha, const double distance) const;
	virtual void updateComponentInfo() {

		int tmp = static_cast<int>(componentValue * 100);
		componentInfo.setString(componentInfoBeginning + std::to_string(tmp) + " %");
	}
};

class CircleRGB : public ColorCircle {

public:
	CircleRGB() : ColorCircle("RGB\nB = ") {

		makeTexture();
		updateComponentInfo();
	}
	virtual ~CircleRGB() = default;

	virtual sf::Color pickColor(const double alpha, const double distance) const;
	virtual void updateComponentInfo() { 

		int tmp = static_cast<int>(componentValue * 255);
		componentInfo.setString(componentInfoBeginning + std::to_string(tmp)); 
	}
};