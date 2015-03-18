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

	bool hasData; // variable to keep track of whether an object has been initialized by the user

protected:
	std::string name_; //name_ of the media item
	int pub_year_; // publication year of the media item
	bool pub_year_def_; // if the publicaiton year is default
	Author* auth_ptr_; // pointer to the author of the mediaitem object

	double price; // price of the media item

	Elements element_[DEF_ELEMENTS]; // any elements that are containend within the media item
	int element_num_;// the element number being worked on

	static int active_; // number of media items active

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