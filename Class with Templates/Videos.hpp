//
//Video Class declaration
//

#ifndef VIDEOS_CLASS_DEF_H_
#define VIDEOS_CLASS_DEF_H_

#include "MediaItems.hpp"
class Videos :
	public MediaItems
{
private:
	std::string director;
	double runTime;

	Videos* sequel_ptr;

public:
	Videos();
	virtual ~Videos();

	//mutators
	virtual int setExecutive(std::string);
	int setRunTime(double);
	int setSequel(Videos*);

	//accessors
	const std::string getDirector();
	const double getRunTime();
	Videos* getSequel();
	const int toCout();

	//predicate
	const int in_mem();
	int clear();
};

#endif