//
//Music Class declaration
//

#ifndef MUSIC_CLASS_DEF_H_
#define MUSIC_CLASS_DEF_H_

#include "MediaItems.hpp"



class Music :
	public MediaItems
{
public:
	enum GENRE {
		ROC, COU, HIP, TEC, REG, OTHER, UDEF, END
	}; //enum of the music genre

private:
	std::string Producer_; //name_ of the producer of the music
	double minutes_; // time in minutes of the music

	GENRE musicGENRE_; //genre enum

public:
	Music();
	~Music();

	//mutators
	virtual int setExecutive(std::string);
	int setrunTime(double);
	int setGENRE(GENRE UDEF);

	//Accessors
	const std::string getProducer();
	const virtual double getrunTime();
	const Music::GENRE getGENRE();
	std::string dispGENRE(Music::GENRE = Music::GENRE::OTHER); // returns a string for outputting the GENRE 
	std::string dispGENRESht(Music::GENRE = Music::GENRE::OTHER); // returns a short string for searching the tokens
	const virtual int toCout();

	//predicate
	const int in_mem();
	int clear();

};

#endif