#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>
class Highscore
{
private:
	int car;
	float timeTaken;
public:
	Highscore();
	~Highscore();
	void setCar(int car);
	void setTimeTaken(float timeTaken);
	int getCar() const;
	float getTimeTaken() const;
	std::string getTime() const;
};
#endif