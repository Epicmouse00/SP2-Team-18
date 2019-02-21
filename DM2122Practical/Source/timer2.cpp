#include "timer2.h"



timer2::timer2()
{
	miliseconds = 0;
	score_miliseconds = 0;
}

timer2::~timer2()
{
}

int timer2::getScoreMinutes() const
{
	return getScoreSeconds() / 60;
}

float timer2::getScoreMiliseconds() const
{
	return score_miliseconds;
}

int timer2::getPrintScoreMiliseconds() const
{
	return (int)score_miliseconds % 100;
}

int timer2::getScoreSeconds() const
{
	return ((int)score_miliseconds / 100) % 60;
}

int timer2::getMinutes() const
{
	return ((int)miliseconds / 100) / 60;
}

float timer2::getMiliseconds() const
{
	return miliseconds;
}

int timer2::getPrintMiliseconds() const
{
	return (int)miliseconds % 100;
}

int timer2::getSeconds() const
{
	return ((int)miliseconds / 100) % 60;
}

void timer2::resetTime()
{
	miliseconds = 0.f;
	score_miliseconds = 0.f;
}

void timer2::setScoreTime()
{
	score_miliseconds = miliseconds;
}

void timer2::updateTime(double dt)
{
	miliseconds += (float)(dt * 100);
}
