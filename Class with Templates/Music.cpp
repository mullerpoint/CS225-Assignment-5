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
#include <list>
#include <vector>
#endif

// include header file
#include "Music.hpp"

//defines for default vaules and text output options
#define DEF_NAME ""
#define DEF_PRICE 0.00
#define DEF_PUB 1970
#define ELEMENT_ZERO 0
#define DEF_Producer_ ""
#define DEF_MIN 0.0
#define DEF_GENRE Music::GENRE::UDEF
#define TEXT_WIDTH 20

//Function prototype for insertion operator
std::ostream& operator<<(std::ostream &out, Music &music);

Music::Music() : MediaItems()
{

	Music::setExecutive(DEF_Producer_);
	Music::setrunTime(DEF_MIN);
	Music::setGENRE(DEF_GENRE);

	Music::modified(false);
}


Music::~Music()
{
	active_--;
}

//Set video director_
int Music::setExecutive(std::string new_Producer_)
{
	Music::Producer_ = new_Producer_;
	Music::modified(true);
	return 0;
}

//set time of music
int Music::setrunTime(double new_minutes_)
{
	if (new_minutes_ >= 0)
	{
		Music::minutes_ = new_minutes_;
		Music::modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a positive value for minutes_";
		return -1;
	}
}

//set GENRE
int Music::setGENRE(GENRE new_GENRE)
{
	Music::musicGENRE_ = new_GENRE;
	Music::modified(true);
	return 0;
}

//get the Producer_ name_
const std::string Music::getProducer()
{
	return Producer_;
}

//get the music time
const double Music::getrunTime()
{
	return minutes_;
}

//get music GENRE
const Music::GENRE Music::getGENRE()
{
	return musicGENRE_;
}

std::string Music::dispGENRE(Music::GENRE type)
{
	switch (type)
	{
	case Music::GENRE::UDEF:
		return "Undefinded";
		break;
	case Music::GENRE::ROC:
		return "Rock";
		break;
	case Music::GENRE::COU:
		return "Country";
		break;
	case Music::GENRE::HIP:
		return "HipHop";
		break;
	case Music::GENRE::TEC:
		return "Techno";
		break;
	case Music::GENRE::REG:
		return  "Reggie";
		break;
	case Music::GENRE::OTHER:
		return "Other";
		break;
	default:
		return "Error : Unrecognized GENRE Type";
		break;
	}
}

std::string Music::dispGENRESht(Music::GENRE type)
{
	switch (type)
	{
	case Music::GENRE::ROC:
		return "ROC";
		break;
	case Music::GENRE::COU:
		return "COU";
		break;
	case Music::GENRE::HIP:
		return "HIP";
		break;
	case Music::GENRE::TEC:
		return "TEC";
		break;
	case Music::GENRE::REG:
		return  "REG";
		break;
	case Music::GENRE::OTHER:
		return "";
		break;
	default:
		return "Error : Unrecognized GENRE Type";
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
	return active_;
}

//clear music object
int Music::clear()
{
	(*this) = Music();
	Music::active_ = Music::active_ - 1;
	return 0;
}

std::ostream& operator<<(std::ostream &out, Music &music)
{

	//check if the item is empty
	if (music.isEmpty() == true); //if empty print nothing
	else if (music.isEmpty() == false) //if not empty print data thats available
	{
		// display item name_ if present
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

		//display Producer_ if set
		if (music.getProducer() == DEF_Producer_);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  director_" << " : " << music.getProducer() << std::endl;
		}

		//display minutes_
		if (music.getrunTime() == DEF_MIN);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  minutes_" << " : " << music.getrunTime() << std::endl;
		}

		//Display GENRE
		//comparing strings to allow comparison, enums refused to compile
		if (music.dispGENRESht(music.getGENRE()) == music.dispGENRESht(Music::GENRE::UDEF));
		else
		{
		out << std::left << std::setw(TEXT_WIDTH) << "  GENRE" << " : " << music.dispGENRE(music.getGENRE()) << std::endl;
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