#include "Highscore.h"



Highscore::Highscore()
{
	car = 0;
	timeTaken = -1.f;
}

Highscore::~Highscore()
{
}

void Highscore::setCar(int car)
{
	this->car = car;
}

void Highscore::setTimeTaken(float timeTaken)
{
	this->timeTaken = timeTaken;
}

int Highscore::getCar() const
{
	return car;
}

float Highscore::getTimeTaken() const
{
	return timeTaken;
}

std::string Highscore::getTime() const
{
	std::string temp;
	temp += std::to_string(((int)timeTaken / 100) / 60);
	temp += ":";
	temp += std::to_string(((int)timeTaken / 100) % 60);
	temp += ":";
	temp += std::to_string((int)timeTaken % 100);
	return temp;
}
