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
	std::string director_; //name_ of the director of the video
	double runTime_; //runtime of the video

	Videos* sequel_ptr_; //pointer to the sequel video item

public:
	Videos();
	virtual ~Videos();

	//mutators
	virtual int setExecutive(std::string);
	int setrunTime(double);
	int setSequel(Videos*);

	//accessors
	const std::string getdirector();
	const double getrunTime();
	Videos* getSequel();
	const int toCout();

	//predicate
	const int in_mem();
	int clear();
};

#endif