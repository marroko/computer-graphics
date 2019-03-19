#include "ColorCircle.h"
#include "Circles.h"

// HSL
sf::Color CircleHSL::pickColor(const double alpha, const double distance) const {

	double h = alpha;
	double s = distance / radius;

	double l = (1 - fabs(2 * componentValue - 1)) * s;
	double x = l * (1 - fabs(fmod(h * 3 / M_PI, 2) - 1));

	double m = componentValue - l / 2;

	double r, g, b;

	if (h <= M_PI3) {
		r = l;
		g = x;
		b = 0;
	}
	else if (h <= M2_PI3) {
		r = x;
		g = l;
		b = 0;
	}
	else if (h <= M_PI) {
		r = 0;
		g = l;
		b = x;
	}
	else if (h <= M4_PI3) {
		r = 0;
		g = x;
		b = l;
	}
	else if (h <= M5_PI3) {
		r = x;
		g = 0;
		b = l;
	}
	else if (h <= M2_PI) {
		r = l;
		g = 0;
		b = x;
	}
	else r = g = b = -255;

	return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

// HSV

sf::Color CircleHSV::pickColor(const double alpha, const double distance) const {

	double h = alpha;
	double s = distance / radius;
	double c = componentValue * s;

	double x = c * (1 - fabs(fmod(h * 3 / M_PI, 2) - 1));
	double m = componentValue - c;

	double r, g, b;

	if (h <= M_PI3) {
		r = c;
		g = x;
		b = 0;
	}
	else if (h <= M2_PI3) {
		r = x;
		g = c;
		b = 0;
	}
	else if (h <= M_PI) {
		r = 0;
		g = c;
		b = x;
	}
	else if (h <= M4_PI3) {
		r = 0;
		g = x;
		b = c;
	}
	else if (h <= M5_PI3) {
		r = x;
		g = 0;
		b = c;
	}
	else if (h <= M2_PI) {
		r = c;
		g = 0;
		b = x;
	}

	return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

// CMY

sf::Color CircleCMY::pickColor(const double alpha, const double distance) const {
	return sf::Color(255 - 255 * (distance / radius), 255 - 255 * (alpha / M2_PI),
		255 - 255 * componentValue);
}

// RGB

sf::Color CircleRGB::pickColor(const double alpha, const double distance) const {
	return sf::Color(255 * (distance / radius), 255 * (alpha / M2_PI), 255 * componentValue);
}