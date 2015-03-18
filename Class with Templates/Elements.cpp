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
int Elements::active = 0;

//constructor
Elements::Elements()
{
	Elements::setEnd(DEF_END);
	Elements::setStart(DEF_START);
	Elements::setName(DEF_NAME);
	Elements::modified(false);
	active++;
}

//destructor
Elements::~Elements()
{
	active--;
}

//display all object attributes
void Elements::toCout()
{
	if (isEmpty());
	else if (!isEmpty())
	{
		if (name == "");
		else if (true)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "Element name" << " : " << name;
		}
		if (start == 0);
		else if (start > 0)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "Start" << " : " << start;
		}
		if (end == 0);
		else if (end > 0)
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
		Elements::end = new_end;
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
		Elements::start = new_start;
		Elements::modified(true);
	}
	else
	{
		std::cout << "Please enter a valid start.";
	}
}

//set element name
void Elements::setName(std::string new_name)
{
	Elements::name = new_name;
	modified(true);
}

//Object empty check
bool Elements::isEmpty()
{
	return !hasData;
}

//set element as modified/unmodified
void Elements::modified(bool data)
{
	Elements::hasData = data;
}

//return objects in memory
int Elements::in_mem()
{
	return active;
}

std::ostream& operator<<(std::ostream &out, Elements &Elem)
{
	//have element name, start, and end set
	if ((Elem.name != DEF_NAME) && (Elem.end != DEF_END) && (Elem.start != DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element Start" << " : " << Elem.start << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element End" << " : " << Elem.end << std::endl;
	}
	//have element name and start set
	else if ((Elem.name != DEF_NAME) && (Elem.end == DEF_END) && (Elem.start != DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element Start" << " : " << Elem.start << std::endl;
	}
	//have element name and end set
	else if ((Elem.name != DEF_NAME) && (Elem.end != DEF_END) && (Elem.start == DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element End" << " : " << Elem.end << std::endl;
	}
	//only have element name set
	else if ((Elem.name != DEF_NAME) && (Elem.end == DEF_END) && (Elem.start == DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.name << std::endl;
	}

	return out;
}

#endif