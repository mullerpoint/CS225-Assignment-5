//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Author Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AUTHOR_CLASS_IMPL_H_
#define AUTHOR_CLASS_IMPL_H_

//Header Files
#include <iostream>
#include <string>
#include <iomanip>
#include "Author.hpp"


//Defines for default vaules
#define DEF_BIRTH 0
#define DEF_DEATH 0
#define DEF_NAME ""
#define TEXT_WIDTH 20

//Active author objects to start
int Author::active = 0;

//Constructor
Author::Author()
{
	Author::setBirth(DEF_BIRTH);
	Author::setDeath(DEF_DEATH);
	Author::setName(DEF_NAME);
	Author::modified(false);
	active++;
}

//Display all atributes
void Author::toCout()
{
	if (name == "");
	else if (true)
	{
		std::cout << std::left << std::setw(TEXT_WIDTH) << " Author name" << " : " << name << std::endl;
	}

	if (birthYear == 0);
	else if (birthYear > 0)
	{
		std::cout << std::left << std::setw(TEXT_WIDTH) << "   Birth Year" << " : " << birthYear << std::endl;
	}

	if (deathYear == 0);
	else if (deathYear > 0)
	{
		std::cout << std::left << std::setw(TEXT_WIDTH) << "   Death Year" << " : " << deathYear << std::endl;
	}
}

//destructor
Author::~Author()
{
	active--;
}

//set the birth year
void Author::setBirth(int new_birth)
{
	if (new_birth >= 0)
	{
		Author::birthYear = new_birth;
		Author::modified(true);
	}
	else
	{
		std::cout << "Please enter a valid birth year.";
	}
}

//set the death year
void Author::setDeath(int new_death)
{
	if (new_death >= 0)
	{
		Author::deathYear = new_death;
		Author::modified(true);
	}
	else
	{
		std::cout << "Please enter a valid death year.";
	}
}

//set the author name
void Author::setName(std::string new_author)
{
	Author::name = new_author;
	Author::modified(true);
}

//get the Author Name
const std::string Author::getName()
{
	return Author::name;
}

//set author as modified/ unmodified
void Author::modified(bool data)
{
	Author::hasData = data;
}

//object empty check
bool Author::isEmpty()
{
	return !hasData;
}

//objects in memory
int Author::in_mem()
{
	return active;
}

std::ostream& operator<<(std::ostream &out, Author &Auth)
{
	out << std::left << std::setw(TEXT_WIDTH) << "  Author" << " : " << Auth.getName() <<std:: endl;
	return out;
}

std::istream& operator>>(std::istream &in, Author &Auth)
{
	int born, died;
	std::string name;

	in >> born;
	Auth.setBirth(born);
	std::cin.ignore(1, '\n');

	in >> died;
	Auth.setDeath(died);
	std::cin.ignore(1, '\n');

	std::getline(in, name);
	Auth.setName(name);

	return in;
}

#endif