//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Media Item Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MEDIAITEMS_CLASS_IMPL_H_
#define MEDIAITEMS_CLASS_IMPL_H_

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

//includes for external dependencies
#ifndef MEDIA_DEPENDENCIES_H_
#define MEDIA_DEPENDENCIES_H_
#include "Author.hpp"
#include "Elements.hpp"
#endif

// include header file
#include "MediaItems.hpp"

//defines for default vaules and text output options
#define DEF_NAME ""
#define DEF_PRICE 0.00
#define DEF_PUB 1970
#define ELEMENT_ZERO 0
#define TEXT_WIDTH 20

//Function prototype for insertion operator
std::ostream& operator<<(std::ostream &out, MediaItems &MI);

//active mediaitem objects to start
int MediaItems::active_ = 0;

//constructor
MediaItems::MediaItems()
{
	MediaItems::setName(DEF_NAME);

	MediaItems::setPrice(DEF_PRICE);

	MediaItems::setPubYear(DEF_PUB);
	pub_year_def_ = true;

	element_num_ = ELEMENT_ZERO;

	setAuthor(NULL);

	hasData = false;

	active_++;
}

//destructor
MediaItems::~MediaItems()
{
	active_--;
}

//set title of book
int MediaItems::setName(std::string new_name_)
{
	MediaItems::name_ = new_name_;
	modified(true);
	return 0;
}

int MediaItems::setPubYear(int new_year)
{
	if (new_year >= 0)
	{
		MediaItems::pub_year_ = new_year;
		MediaItems::pub_year_def_ = false;
		modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a valid Year.";
		return -1;
	}
}

//set the Media Item price - validate that the price is not negative
int MediaItems::setPrice(double new_price)
{
	if (new_price >= 0)
	{
		MediaItems::price = new_price;
		modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a valid positive price.";
		return -1;
	}
}

//set item elements
int MediaItems::setElement(int start, int end, std::string name_, int elementNum)
//elementNum is not used but I included it to make it easier to change the program over later
{
	element_[element_num_].setStart(start);
	element_[element_num_].setEnd(end);
	element_[element_num_].setName(name_);
	MediaItems::element_num_++;
	modified(true);
	return 0;
}

//set author
int MediaItems::setAuthor(Author* new_author)
{
	MediaItems::auth_ptr_ = new_author;
	MediaItems::modified(true);
	return 0;
}

//print out item
const int MediaItems::toCout()
{
	std::cout << (*this);
	return 0;
}

//get book title
const std::string MediaItems::getName()
{
	return MediaItems::name_;
}

//get pulication year
const int MediaItems::getPubYear()
{
	return MediaItems::pub_year_;
}

// get if the publication year is default
const bool MediaItems::getPubYearDef()
{
	return MediaItems::pub_year_def_;
}

//get author pointer
Author* MediaItems::getAuthor()
{
	return MediaItems::auth_ptr_;
}

//get price of item
const double MediaItems::getPrice()
{
	return MediaItems::price;
}

//get the address of an elemtent in the array
Elements* MediaItems::getElements(int elementNum)
{
	Elements* elem_addr = &element_[elementNum];

	return elem_addr;
}

//returns if the item is empty
const bool MediaItems::isEmpty()
{
	return !(hasData);
}

// set a modified flag
int MediaItems::modified(bool data)
{
	MediaItems::hasData = data;
	return 0;
}

//return the number of constructed items
const int MediaItems::in_mem()
{
	return active_;
}

int MediaItems::clear()
{
	(*this) = MediaItems();
	MediaItems::active_ = MediaItems::active_ - 1; //active is increased when calling the constructor
	return 0;
}

std::ostream& operator<<(std::ostream &out, MediaItems &MI)
{
	//check if the item is empty
	if (MI.isEmpty() == true); //if empty print nothing
	else if (MI.isEmpty() == false) //if not empty print data thats available
	{
		// display item name_ if present
		if (MI.getName() == DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item Name" << " : " << "No Name Set" << std::endl;
		}
		else if (MI.getName() != DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item" << " : " << MI.getName() << std::endl;
		}

		// print out the author object
		if (MI.getAuthor() == NULL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << (*MI.getAuthor());
		}

		//display publication year if set; check if the value is default
		if (MI.getPubYearDef() == true);
		else if (MI.getPubYearDef() == false)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Pub Year" << " : " << MI.getPubYear() << std::endl;
		}

		//display price if set
		if (MI.getPrice() == DEF_PRICE);
		else if (MI.getPrice() != DEF_PRICE)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Price" << " : $" << std::fixed << MI.getPrice() << std::endl;
		}

		//display elements if they exist; 
		if ((*MI.getElements(0)).isEmpty() == true);
		else if ((*MI.getElements(0)).isEmpty() == false)
		{
			int count = 0;
			while ((*MI.getElements(count)).isEmpty() == false)
			{
				out << (*MI.getElements(count));
				count++;
			}
		}
	}
	return out;
}

#endif