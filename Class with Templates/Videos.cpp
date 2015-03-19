//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Video Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VIDEOS_CLASS_IMPL_H_
#define VIDEOS_CLASS_IMPL_H_

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
#include "Videos.hpp"

//defines for default vaules and text output options
#define DEF_NAME ""
#define DEF_PRICE 0.00
#define DEF_PUB 1970
#define ELEMENT_ZERO 0
#define DEF_director_ ""
#define DEF_runTime_ 0.0
#define TEXT_WIDTH 20

//Function prototype for insertion operator
std::ostream& operator<<(std::ostream &out, Videos &Video);

Videos::Videos() : MediaItems()
{
	Videos::setExecutive(DEF_director_);
	Videos::setrunTime(DEF_runTime_);
	Videos::setSequel(NULL);

	Videos::modified(false);
}


Videos::~Videos()
{
	active_--;
}

//Set video director_
int Videos::setExecutive(std::string new_director_)
{
	Videos::director_ = new_director_;
	Videos::modified(true);
	return 0;
}

//Set Video Run time
int Videos::setrunTime(double new_runTime_)
{
	if (new_runTime_ >= 0)
	{
		Videos::runTime_ = new_runTime_;
		Videos::modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a positive run time";
		return -1;
	}
}

//Set Sequel
int Videos::setSequel(Videos* new_sequel)
{
	Videos::sequel_ptr_ = new_sequel;
	Videos::modified(true);
	return 0;
}

//get director_
const std::string Videos::getdirector()
{
	return director_;
}

//get run time
const double Videos::getrunTime()
{
	return runTime_;
}

//get sequel pointer
Videos* Videos::getSequel()
{
	return sequel_ptr_;
}

const int Videos::toCout()
{
	std::cout << (*this);
	return 0;
}

//return the number of constructed items
const int Videos::in_mem()
{
	return active_;
}

int Videos::clear()
{
	(*this) = Videos();
	Videos::active_ = Videos::active_ - 1;
	return 0;
}

std::ostream& operator<<(std::ostream &out, Videos &Video)
{

	//check if the item is empty
	if (Video.isEmpty() == true); //if empty print nothing
	else if (Video.isEmpty() == false) //if not empty print data thats available
	{
		// display item name_ if present
		if (Video.getName() == DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item Name" << " : " << "No Name Set" << std::endl;
		}
		else if (Video.getName() != DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item" << " : " << Video.getName() << std::endl;
		}

		// print out the author object
		if (Video.getAuthor() == NULL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << (*(Video.getAuthor()));
		}

		//display publication year if set; check if the value is default
		if (Video.getPubYearDef() == true);
		else if (Video.getPubYearDef() == false)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Pub Year" << " : " << Video.getPubYear() << std::endl;
		}

		//display price if set
		if (Video.getPrice() == DEF_PRICE);
		else if (Video.getPrice() != DEF_PRICE)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Price" << " : $" << std::fixed << Video.getPrice() << std::endl;
		}

		//display director_ if set
		if (Video.getdirector() == DEF_director_);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  director_" << " : " << Video.getdirector() << std::endl;
		}

		//display runTime_ if set
		if (Video.getrunTime() == DEF_runTime_);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  runTime_" << " : " << Video.getrunTime();
		}

		//display sequel if set
		if (Video.getSequel() == NULL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Sequel" << " : " << (*(Video.getSequel())).getName();
		}

		//display elements if they exist; 
		if ((*Video.getElements(0)).isEmpty() == true);
		else if ((*Video.getElements(0)).isEmpty() == false)
		{
			int count = 0;
			while ((*Video.getElements(count)).isEmpty() == false)
			{
				out << (*Video.getElements(count));
				count++;
			}
		}
	}
	return out;
}

#endif