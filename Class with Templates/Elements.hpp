//
//Elements Class declaration
//

#ifndef ELEMENTS_CLASS_DEF_H_
#define ELEMENTS_CLASS_DEF_H_

class Elements
{
private:
	int start;
	int end;
	std::string name;

	bool hasData;

	static int active;

public:
	Elements();
	~Elements();
	void setStart(int);
	void setEnd(int);
	void setName(std::string);
	void modified(bool);
	bool isEmpty();
	int in_mem();
	void toCout();

	friend std::ostream& operator<<(std::ostream &out, Elements &Elem);
};

#endif