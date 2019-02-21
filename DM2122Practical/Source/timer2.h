#ifndef TIMER2_H 
#define TIMER2_H

class timer2
{
private:
	float miliseconds; //Technically not milliseconds, but rather similar to dt
	float score_miliseconds;
public:
	timer2();
	~timer2();
	int getScoreMinutes() const;
	float getScoreMiliseconds() const;
	int getPrintScoreMiliseconds() const;
	int getScoreSeconds() const;
	int getMinutes() const;
	float getMiliseconds() const;
	int getPrintMiliseconds() const;
	int getSeconds() const;
	void resetTime();
	void setScoreTime();
	void updateTime(double dt);
};
#endif