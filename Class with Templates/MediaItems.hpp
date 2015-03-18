//
//Media Item Class declaration
//
#ifndef MEDIAITEMS_CLASS_DEF_H_
#define MEDIAITEMS_CLASS_DEF_H_

#define DEF_ELEMENTS 15

#ifndef MEDIA_DEPENDENCIES_H_
#define MEDIA_DEPENDENCIES_H_
#include "Author.hpp"
#include "Elements.hpp"
#endif

class MediaItems
{
private:

	bool hasData;

protected:
	std::string name;
	int pub_year;
	bool pub_year_def;
	Author* auth_ptr;

	double price;

	Elements element[DEF_ELEMENTS];
	int element_num;

	static int active;

public:
	MediaItems();
	virtual ~MediaItems();

	//mutators
	int setName(std::string);
	int setPubYear(int);
	int setPrice(double);
	int setElement(int, int, std::string, int);
	int setAuthor(Author*);

	//Accessors
	const std::string getName();
	const int getPubYear();
	const bool getPubYearDef();
	Author* getAuthor();
	const double getPrice();
	Elements* getElements(int = 0);
	const virtual int toCout();

	//Predicate Functions
	const virtual bool isEmpty();
	virtual int modified(bool);
	const int in_mem();
	virtual int clear();
};

#endif