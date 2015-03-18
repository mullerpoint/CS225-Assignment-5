//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Music Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MUSIC_CLASS_IMPL_H_
#define MUSIC_CLASS_IMPL_H_

#ifndef MEDIA_DEPENDENCIES_CORE_H_
#define MEDIA_DEPENDENCIES_CORE_H_
#include <iostream> //default include
#include <string> // included to get strings to work
#include <locale> // included to get locale info for output
#include <io.h> // isatty for windows
//#include <unistd.h> // isatty  for linux
#include <iomanip> // included to make pretty output
#include <typeinfo>
#endif

// include header file
#include "Music.hpp"

//defines for default vaules and text output options
#define DEF_NAME ""
#define DEF_PRICE 0.00
#define DEF_PUB 1970
#define ELEMENT_ZERO 0
#define DEF_PRODUCER ""
#define DEF_MIN 0.0
#define DEF_GENRE Music::Genre::UDEF
#define TEXT_WIDTH 20

//Function prototype for insertion operator
std::ostream& operator<<(std::ostream &out, Music &music);

Music::Music() : MediaItems()
{

	Music::setExecutive(DEF_PRODUCER);
	Music::setRunTime(DEF_MIN);
	Music::setGenre(DEF_GENRE);

	Music::modified(false);
}


Music::~Music()
{
	active--;
}

//Set video Director
int Music::setExecutive(std::string new_producer)
{
	Music::Producer = new_producer;
	Music::modified(true);
	return 0;
}

//set time of music
int Music::setRunTime(double new_Minutes)
{
	if (new_Minutes >= 0)
	{
		Music::minutes = new_Minutes;
		Music::modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a positive value for minutes";
		return -1;
	}
}

//set genre
int Music::setGenre(Genre new_genre)
{
	Music::musicGenre = new_genre;
	Music::modified(true);
	return 0;
}

//get the producer name
const std::string Music::getProducer()
{
	return Producer;
}

//get the music time
const double Music::getRunTime()
{
	return minutes;
}

//get music genre
const Music::Genre Music::getGenre()
{
	return musicGenre;
}

std::string Music::dispGenre(Music::Genre type)
{
	switch (type)
	{
	case Music::Genre::UDEF:
		return "Undefinded";
		break;
	case Music::Genre::ROC:
		return "Rock";
		break;
	case Music::Genre::COU:
		return "Country";
		break;
	case Music::Genre::HIP:
		return "HipHop";
		break;
	case Music::Genre::TEC:
		return "Techno";
		break;
	case Music::Genre::REG:
		return  "Reggie";
		break;
	case Music::Genre::OTHER:
		return "Other";
		break;
	default:
		return "Error : Unrecognized Genre Type";
		break;
	}
}

std::string Music::dispGenreSht(Music::Genre type)
{
	switch (type)
	{
	case Music::Genre::ROC:
		return "ROC";
		break;
	case Music::Genre::COU:
		return "COU";
		break;
	case Music::Genre::HIP:
		return "HIP";
		break;
	case Music::Genre::TEC:
		return "TEC";
		break;
	case Music::Genre::REG:
		return  "REG";
		break;
	case Music::Genre::OTHER:
		return "";
		break;
	default:
		return "Error : Unrecognized Genre Type";
		break;
	}
}

const int Music::toCout()
{
	std::cout << (*this);
	return 0;
}

//return the number of constructed items
const int Music::in_mem()
{
	return active;
}

//clear music object
int Music::clear()
{
	(*this) = Music();
	Music::active = Music::active - 1;
	return 0;
}

std::ostream& operator<<(std::ostream &out, Music &music)
{

	//check if the item is empty
	if (music.isEmpty() == true); //if empty print nothing
	else if (music.isEmpty() == false) //if not empty print data thats available
	{
		// display item name if present
		if (music.getName() == DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item Name" << " : " << "No Name Set" << std::endl;
		}
		else if (music.getName() != DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item" << " : " << music.getName() << std::endl;
		}

		// print out the author object
		if (music.getAuthor() == NULL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << (*(music.getAuthor()));
		}

		//display publication year if set; check if the value is default
		if (music.getPubYearDef() == true);
		else if (music.getPubYearDef() == false)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Pub Year" << " : " << music.getPubYear() << std::endl;
		}

		//display price if set
		if (music.getPrice() == DEF_PRICE);
		else if (music.getPrice() != DEF_PRICE)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Price" << " : $" << std::fixed << music.getPrice() << std::endl;
		}

		//display producer if set
		if (music.getProducer() == DEF_PRODUCER);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Director" << " : " << music.getProducer() << std::endl;
		}

		//display minutes
		if (music.getRunTime() == DEF_MIN);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Minutes" << " : " << music.getRunTime() << std::endl;
		}

		//Display genre
		//comparing strings to allow comparison, enums refused to compile
		if (music.dispGenreSht(music.getGenre()) == music.dispGenreSht(Music::Genre::UDEF));
		else
		{
		out << std::left << std::setw(TEXT_WIDTH) << "  Genre" << " : " << music.dispGenre(music.getGenre()) << std::endl;
		}

		//display elements if they exist; 
		if ((*music.getElements(0)).isEmpty() == true);
		else if ((*music.getElements(0)).isEmpty() == false)
		{
			int count = 0;
			while ((*music.getElements(count)).isEmpty() == false)
			{
				out << (*music.getElements(count));
				count++;
			}
		}
	}
	return out;
}

#endif