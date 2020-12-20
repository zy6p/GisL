#include "MyRGB.h"
#include <math.h>


MyRGB::MyRGB()
{
}


MyRGB::~MyRGB()
{
}

int MyRGB::R()
{
	return this->r;
}

int MyRGB::G()
{
	return this->g;
}

int MyRGB::B()
{
	return this->b;
}


float MyRGB::NR()
{
	return r * 1.0 / 256;
}

float MyRGB::NG()
{
	return g * 1.0 / 256;
}

float MyRGB::NB()
{
	return b * 1.0 / 256;
}

void MyRGB::setR(int r)
{
	if (r >= 0 && r <= 255) {
		this->r = r;
	}
}

void MyRGB::setG(int g)
{
	if (g >= 0 && g <= 255) {
		this->g = g;
	}
}

void MyRGB::setB(int b)
{
	if (b >= 0 && b <= 255) {
		this->b = b;
	}
}

void MyRGB::setNR(float nr)
{
	if (nr >= 0.0 && nr <= 1.0) {
		this->r = floor(nr * 256 + 0.5);
	}
}

void MyRGB::setNG(float ng)
{
	if (ng >= 0.0 && ng <= 1.0) {
		this->g = floor(ng * 256 + 0.5);
	}
}

void MyRGB::setNB(float nb)
{
	if (nb >= 0.0 && nb <= 1.0) {
		this->b = floor(nb * 256 + 0.5);
	}
}

void MyRGB::fromRGB(int r, int g, int b)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
}

void MyRGB::fromNRGB(float r, float g, float b)
{
	if (r >= 0.0 && r <= 1.0 && g >= 0.0 && g <= 1.0 && b >= 0.0 && b <= 1.0) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
}
