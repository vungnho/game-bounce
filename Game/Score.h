#pragma once
#include <Utilities/MyMath.h>

#define CDTIME_SHOW_SCORE 1.0


class Score
{
public:
	Score();
	~Score(void);
	
	char name[256];
	char strScore[256];
	char strHightScore[256];
	char strScorePlus[256];
	Vector2 position;

	void logScore();
	void update(float dt);

	void setDefault();
	int getNumScore();
	int getScore();
	const char* getStringScore();
	const char* getStringHightScore();
	const char* getStringScorePlus();
	void addNumScore(int n=1);
	void saveScore();

private:
	static int preScore;
	const static int deltaScore = 5;
	int numScore;
	int hightScore;
	int scorePlus;
	float coolDownTimeShow;
	
	void loadScore();
	void numScore_2_strScore();
};
