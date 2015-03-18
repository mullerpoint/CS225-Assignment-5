//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Elements Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ELEMENTS_CLASS_IMPL_H_
#define ELEMENTS_CLASS_IMPL_H_

//Header Files
#include <iostream>
#include <string>
#include <iomanip>
#include "Elements.hpp"


//Defines for default vaules
#define DEF_START 0
#define DEF_END 0
#define DEF_NAME ""
#define TEXT_WIDTH 20

//Active elements objects to start
int Elements::active_ = 0;

//constructor
Elements::Elements()
{
	Elements::setEnd(DEF_END);
	Elements::setStart(DEF_START);
	Elements::setName(DEF_NAME);
	Elements::modified(false);
	active_++;
}

//destructor
Elements::~Elements()
{
	active_--;
}

//display all object attributes
void Elements::toCout()
{
	if (isEmpty());
	else if (!isEmpty())
	{
		if (name_ == "");
		else if (true)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "Element name" << " : " << name_;
		}
		if (start_ == 0);
		else if (start_ > 0)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "Start" << " : " << start;
		}
		if (end_ == 0);
		else if (end_ > 0)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "End" << " : " << end;
		}

	}
}

//set element end
void Elements::setEnd(int new_end)
{
	if (new_end >= 0)
	{
		Elements::end_ = new_end;
		Elements::modified(true);
	}
	else
	{
		std::cout << "Please enter a valid end.";
	}
}

//set element start
void Elements::setStart(int new_start)
{
	if (new_start >= 0)
	{
		Elements::start_ = new_start;
		Elements::modified(true);
	}
	else
	{
		std::cout << "Please enter a valid start.";
	}
}

//set element name
void Elements::setName(std::string new_name_)
{
	Elements::name_ = new_name_;
	modified(true);
}

//Object empty check
bool Elements::isEmpty()
{
	return !hasData_;
}

//set element as modified/unmodified
void Elements::modified(bool data)
{
	Elements::hasData_ = data;
}

//return objects in memory
int Elements::in_mem()
{
	return active_;
}

std::ostream& operator<<(std::ostream &out, Elements &Elem)
{
	//have element name_, start, and end set
	if ((Elem.name_ != DEF_NAME) && (Elem.end_ != DEF_END) && (Elem.start_ != DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name_ << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element Start" << " : " << Elem.start_ << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element End" << " : " << Elem.end_ << std::endl;
	}
	//have element name_ and start set
	else if ((Elem.name_ != DEF_NAME) && (Elem.end_ == DEF_END) && (Elem.start_ != DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name_ << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element Start" << " : " << Elem.start_ << std::endl;
	}
	//have element name_ and end set
	else if ((Elem.name_ != DEF_NAME) && (Elem.end_ != DEF_END) && (Elem.start_ == DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name_ << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element End" << " : " << Elem.end_ << std::endl;
	}
	//only have element name_ set
	else if ((Elem.name_ != DEF_NAME) && (Elem.end_ == DEF_END) && (Elem.start_ == DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name_ << std::endl;
	}

	return out;
}

#endif