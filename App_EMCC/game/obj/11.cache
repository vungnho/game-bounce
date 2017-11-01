#include "StdAfx.h"
#include "Score.h"
#include "String.h"
#include "Globals.h"
int Score::preScore = 0;
Score::Score(void)
{
	this->numScore = preScore;
	this->hightScore = 0;
	this->scorePlus = 0;
	loadScore();
	numScore_2_strScore();
}
void Score::setDefault()
{
	this->preScore = 0;
	this->numScore = preScore;
	this->hightScore = 0;
	loadScore();
	numScore_2_strScore();
}
Score::~Score(void)
{
	
}
int Score::getNumScore()
{
	return this->numScore;
}
int Score::getScore()
{
	return this->numScore*deltaScore;
}
void Score::addNumScore(int n)
{
	this->scorePlus = n;
	this->numScore += n;
	if(this->hightScore < this->numScore) this->hightScore = this->numScore;
	this->coolDownTimeShow = CDTIME_SHOW_SCORE;
	this->numScore_2_strScore();
}
void Score::numScore_2_strScore()
{
	sprintf ( this->strScore, "%d", this->numScore*deltaScore );
	sprintf ( this->strHightScore, "%d", this->hightScore*deltaScore );
	if(this->scorePlus>0)
	{
		sprintf ( this->strScorePlus, "+%d", this->scorePlus*deltaScore );
	}
	else if(this->scorePlus<0)
	{
		sprintf ( this->strScorePlus, "%d", this->scorePlus*deltaScore );
	}
	else
	{
		sprintf ( this->strScorePlus, "  ");
	}
}
void Score::logScore()
{
	preScore = numScore;
}
void Score::update(float dt)
{
	if(this->scorePlus)
	{
		if(this->coolDownTimeShow > 0)
		{
			this->coolDownTimeShow -= dt;
		}
		else
		{
			this->scorePlus = 0;
			numScore_2_strScore();
		}
	}
}
const char * Score::getStringScore()
{
	return this->strScore;
}
const char * Score::getStringHightScore()
{
	return this->strHightScore;
}
const char* Score::getStringScorePlus()
{
	return this->strScorePlus;
}
void Score::loadScore()
{
	const char * file_name = String::concat( BOUNCE_DATA_LOCATION, "Data/Score.txt");
	FILE* file = fopen(file_name, "r");
	if(file == NULL)
	{
		Console::log("Can not open to read file %s.\n", file_name);
		return;
	}
	if(fscanf(file, "%s %d", this->name, &this->hightScore))
	{
		this->hightScore /= deltaScore;
		//Console::log("Read file %s successfully.(%d)\n", file_name,this->hightScore);
	}
	fclose(file);
	delete[] file_name;
}
void Score::saveScore()
{
	const char * file_name = String::concat( BOUNCE_DATA_LOCATION, "Data/Score.txt");
	FILE *file = fopen(file_name, "w+");

	if(file == NULL) 
	{
		Console::log("Can not open to write file %s.\n", file_name);
		return;
	}

	fprintf(file, "%s %s", this->name, this->strHightScore);
	fclose(file);
	delete[] file_name;
}