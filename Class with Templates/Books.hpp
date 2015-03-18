//
//Book Class declaration
//

#ifndef BOOKS_CLASS_DEF_H_
#define BOOKS_CLASS_DEF_H_

#include "MediaItems.hpp"
class Books :
	public MediaItems
{
private:
	std::string isbn;
	int pages;
	bool in_print;
	bool in_print_def;
	Books* sequel_ptr;


public:
	Books();
	virtual ~Books();

	//mutators
	int setPages(int);
	int setInPrint(bool);
	int setSequel(Books*);
	int setISBN(std::string);

	//Accessors
	const int getPages();
	const bool getInPrint();
	const bool getInPrintDef();
	Books* getSequel();
	const std::string getISBN();
	const int toCout();

	//predicate
	const int in_mem();
	int clear();
};

#endif