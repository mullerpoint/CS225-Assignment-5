//
//Author Class declaration
//

#ifndef AUTHOR_CLASS_DEF_H_
#define AUTHOR_CLASS_DEF_H_

class Author
{
private:
	int birthYear_; // birth year of the author
	int deathYear_; // death year of the author
	std::string name_; // name of the author

	bool hasData_; // variable to keep track of whether an object has been initialized by the user

	static int active_; //number of active author objects

public:
	Author();
	~Author();
	const std::string getName();
	void setBirth(int);
	void setDeath(int);
	void setName(std::string);
	void modified(bool);
	bool isEmpty();
	int in_mem();
	void toCout();

	friend std::ostream& operator<<(std::ostream &out, Author &Auth);
	friend std::istream& operator>>(std::istream &in, Author &Auth);
};

#endif