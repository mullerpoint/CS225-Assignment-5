//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Spring 2015
// CS 225 Assignment 4
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Header files standard libraries and classes
#ifndef MEDIA_DEPENDENCIES_CORE_H_
#define MEDIA_DEPENDENCIES_CORE_H_
#include <iostream> //default include
#include <string> // included to get strings to work
#include <locale> // included to get locale info for output
#include <io.h> // isatty for windows
//#include <unistd.h> // isatty  for linux
#include <iomanip> // included to make pretty output
#include <typeinfo> //included to use typeid()
#include <list> //included for use of list template
#include <vector> //included for use of vector template
#endif

//User Defined Class Includes
#include "Author.hpp"
#include "Elements.hpp"
#include "MediaItems.hpp"
#include "Books.hpp"
#include "Music.hpp"
#include "Videos.hpp"


//Gloabal Variables and Defines
#define TEXT_WIDTH 20
bool done = false;

//determine if interactive or scripted
int interactive = _isatty(_fileno(stdin)); //windowns statement
//int interactive = isatty(STDIN_FILENO); //unix statement

//define global pointers for media item objects
std::vector<MediaItems *>items;
int ItemNum = 0;
int totalItems = 0;
//

//define global pointers for author objects
std::vector<Author *>Authors;
int AuthNum = 0;
int totalAuths = 0;
//

//define global locale pointer for the locale imbue functionality
std::locale* locale;
//

//Function Prototypes
int init_mixed_array();
void process_menu_in(char);
void print_menu();
void print_Authors();
void print_MediaItems();
//


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Main Declaration
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

	//use the imbue functionality to make the output look pretty
	std::locale mylocal("");
	locale = &mylocal;
	std::cout.imbue(*locale);

	//core program 
	std::string menu_in;
	print_menu();


	if (interactive)
	{
		while (!done)
		{
			std::cout << std::endl << "Menu [" << ItemNum << "]: ";
			std::getline(std::cin, menu_in);
			process_menu_in(menu_in[0]);
		}
	}
	else if (!interactive)
	{
		while (!done)
		{
			std::cout << std::endl << "Menu [" << ItemNum << "]: ";
			std::cin >> menu_in;
			process_menu_in(menu_in[0]);
		}
	}
	std::cout << std::endl << "Goodbye" << std::endl;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Function Declarations
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Process Menu Function
void process_menu_in(char inchar)
{
	std::cout.imbue(*locale);
	std::cout.precision(2);

	switch (toupper(inchar))
	{

	case '/':
	{
		std::string junk_line;
		std::getline(std::cin, junk_line);
	}
	break;

	// Print all objects
	case '*':
	{
		//Print out all author objects
		std::cout << std::endl << std::endl << "==== All Authors Start ====" << std::endl;
		int count = 0;
		while (count <= (totalAuths - 1))
		{
			if ((*Authors[count]).isEmpty());
			//isempty() returns the hasData value which is false for an object with no data and true for an object with data, hence the ! to invert the return value
			else
			{
				std::cout << std::endl << "Author [" << count << "] :" << std::endl;
				(*Authors[count]).toCout();
			}
			count++;
		}

		std::cout << std::endl << std::endl << std::left << std::setw(TEXT_WIDTH) << "  Authors in Memory" << " : " << (*Authors[0]).in_mem() << std::endl
			<< std::left << std::setw(TEXT_WIDTH) << "    Memory Used" << " : " << sizeof(Author)*(*Authors[0]).in_mem() << " Bytes";

		std::cout << std::endl << "===== All Authors End =====" << std::endl;

		//Print out all Media Item Objects
		std::cout << std::endl << std::endl << "===== All Items Start =====" << std::endl;
		count = 0;
		while (count <= (totalItems - 1))
		{
			if ((*items[count]).isEmpty());
			else //if (mixed_array[count].isEmpty() == true)
			{
				std::cout << std::endl << "Item [" << count << "]" << std::endl;
				(*items[count]).toCout();
			}
			count++;
		}

		std::cout << std::endl << std::endl << std::left << std::setw(TEXT_WIDTH) << "  Items in Memory" << " : " << (*items[0]).in_mem() << std::endl
			<< std::left << std::setw(TEXT_WIDTH) << "    Memory Used" << " : " << sizeof(MediaItems)*(*items[0]).in_mem() << " Bytes";

		std::cout << std::endl << "====== All Items End ======" << std::endl;

		std::cout << std::endl << std::left << std::setw(TEXT_WIDTH) << "  Total Memory Used" << " : " << (sizeof(MediaItems)*(*items[0]).in_mem()) + (sizeof(Author)*(*Authors[0]).in_mem()) << " Bytes";
	}
	break;

	//increase item number by 1
	case '+':
	{
		//TODO: function that asks for item type and create the item
		//query user as to what kind of item they want to add
		std::cout << "What kind of item do you want to add : (M)usic, (V)ideo, (B)ook, (I)tem" << std::endl;
		std::string type;
		MediaItems* item_ptr;

		//based on if the session is interactive read in the type
		if (interactive)
		{
			std::getline(std::cin, type);
		}
		else if (!interactive)
		{
			std::cin >> type;
		}


		//based on the type create the item
		switch (toupper(type[0]))
		{
		case 'M':
			item_ptr = new Music;
			break;

		case 'V':
			item_ptr = new Videos;
			break;

		case 'B':
			item_ptr = new Books;
			break;

		default:
			item_ptr = new MediaItems;
			break;
		}


		items.push_back(item_ptr);
		totalItems++;
		ItemNum = totalItems;
	}
	break;

	//decrease item number by 1
	case '-':
	{
		//TODO: function that deletes the current item


		
		totalItems--;
	}
	break;

	// set a custom item number between 0-totalItems
	case '#':
	{
		//declare temp vaiable and read in user value
		int new_itemNum;
		std::cout << "Enter new item number : ";
		std::cin >> new_itemNum;

		//validate input
		if ((new_itemNum >= 0) && (new_itemNum <= (totalItems - 1)))
		{
			ItemNum = new_itemNum;
		}
		else{
			std::cout << "Please enter a valid number beteen 0-" << totalItems;
		}

		//clear buffer for next input
		std::cin.ignore(10000, '\n');
		std::cout << std::endl;
	}
	break;

	// clear item menu option
	case '0':
	{
		(*items[ItemNum]).clear();
		std::cout << "Item " << ItemNum << " Cleared" << std::endl;
	}
	break;

	//set media item duration or time
	case 'B':
	{
		if (!(typeid(items[ItemNum]) == typeid(Books) || typeid(items[ItemNum]) == typeid(MediaItems)))
		{
			double runTime;
			std::cout << "Please enter the run time : ";
			std::cin >> runTime;
			if (typeid(items[ItemNum]) == typeid(Music))
			{
				Music* music_ptr = (Music*)items[ItemNum];
				(*music_ptr).setrunTime(runTime);
			}
			else
			{
				Videos* video_ptr = (Videos*)(items[ItemNum]);
				(*video_ptr).setrunTime(runTime);
			}

		}
		else
		{
			std::cout << "Error : you cannot set the runTime on a Book or Media Item object" << std::endl;
		}
	}
	break;

	//Create an author object
	case 'C':
	{
		Author* temp_ptr = new Author;
		Authors.push_back(temp_ptr);
		totalAuths++;
		AuthNum = totalAuths;
		
		int born, died;
		std::string name;

		if (interactive)
		{
			std::cout << "Please enter the Authors name :";
			std::getline(std::cin, name);
			(*Authors[AuthNum]).setName(name);


			std::cout << "Please enter the Authors birth year (yyyy), Zero(0) for none :";
			std::cin >> born;
			(*Authors[AuthNum]).setBirth(born);
			std::cin.ignore(10000, '\n');

			std::cout << "Please enter the Authors death year (yyyy), Zero(0) for none :";
			std::cin >> died;
			(*Authors[AuthNum]).setDeath(died);
			std::cin.ignore(10000, '\n');

			AuthNum = AuthNum + 1;
		}
		else //scripted
		{
			std::cin >> (*Authors[AuthNum]);
			//std::cin.ignore(256, '\n');

			AuthNum = AuthNum + 1;
		}
	}
	break;

	// display item menu option
	case 'D':
	{
		std::cout << std::endl << "Item [" << ItemNum << "] :" << std::endl;
		(*items[ItemNum]).toCout();
	}
	break;

	//Create an element object in the media item object
	case 'E':
	{
		int num, start, end;
		std::string name;

		if (interactive)
		{
			std::cout << "Please enter the Element name_ : ";
			std::getline(std::cin, name);

			std::cout << "Please enter the Element start, Zero(0) for none : ";
			std::cin >> start;
			std::cin.ignore(1, '\n');

			std::cout << "Please enter the Element end, Zero(0) for none : ";
			std::cin >> end;
			std::cin.ignore(1, '\n');

		}
		else //scripted
		{
			std::cin >> start;
			std::cin.ignore(1, '\n');

			std::cin >> end;
			std::cin.ignore(1, '\n');

			std::getline(std::cin, name);
			(*Authors[AuthNum]).setName(name);
		}


		(*items[ItemNum]).addElement(start, end, name, num = 0);

	}
	break;

	//set music/video Producer/director respectivly
	case 'F':
	{
		if (!(typeid(*items[ItemNum]) == typeid(Books) || typeid(*items[ItemNum]) == typeid(MediaItems)))
		{
			std::string executive;
			std::cout << "Please enter the Producer or director : ";
			std::getline(std::cin, executive);


			if (typeid(*items[ItemNum]) == typeid(Music))
			{
				//create a simple variable that points to cast version of the object
				Music* music_ptr = (Music*)items[ItemNum];
				//set the Producer
				(*music_ptr).setExecutive(executive);
			}
			else
			{
				//create a simple variable that points to cast version of the object
				Videos* video_ptr = (Videos*)items[ItemNum];
				//set the director
				(*video_ptr).setExecutive(executive);
			}
		}
		else
		{
			std::cout << "Error : you cannot set the Producer or director on a Book or Media Item object" << std::endl;
		}
	}
	break;

	// set the item in print status
	case 'I':
	{
		if (typeid(*items[ItemNum]) == typeid(Books))
		{
			//create a simple variable that points to cast version of the object
			Books* book_ptr = (Books*)items[ItemNum];

			bool printStatus;
			std::cout << "Is the book still in print (0/1) : ";
			std::cin >> printStatus;
			std::cin.ignore(10000, '\n');
			(*book_ptr).setInPrint(printStatus);
		}
	}
	break;

	//set Book ISBN
	case 'J':
	{
		if (typeid(*items[ItemNum]) == typeid(Books))
		{
			//create a simple variable that points to cast version of the object
			Books* book_ptr = (Books*)items[ItemNum];

			std::string isbn;
			std::cout << "Please enter the Book ISBN :";
			std::getline(std::cin, isbn);
			(*book_ptr).setISBN(isbn);
		}
		else
		{
			std::cout << "Error : non-book item cannot have an ISBN";
		}
	}
	break;

	//set Music GENRE
	case 'K':
	{
		if (typeid(*items[ItemNum]) == typeid(Music))
		{
			//create a simple variable that points to cast version of the object
			Music* music_ptr = (Music*)items[ItemNum];

			//get the GENRE string from input
			std::string GenreStr;
			std::cout << "Please enter the GENRE : ";
			std::getline(std::cin, GenreStr);
			for (auto & c : GenreStr) c = toupper(c); //convert to uppercase

			//create a bool variable to determine if the GENRE has been set
			bool GENRESet = false;

			//variable to keep track of type
			Music::GENRE type = Music::GENRE::ROC;

			//for loop to try find a match to one of the defined GENREs
			while ((type != Music::GENRE::END) && (GENRESet == false))
			{
				//get the token for searching the GENRE string
				std::string typeStr = (*music_ptr).dispGENRESht(type);

				//if the token matches something in the GENRE string set the object to the GENRE
				if (GenreStr.find(typeStr) != std::string::npos)
				{
					(*music_ptr).setGENRE(type);
					GENRESet = true;
				} //if GenreStr
				type = Music::GENRE(type + 1);
			}//while
			if (GENRESet == false)
			{
				(*music_ptr).setGENRE(Music::GENRE::OTHER);
			}
		} //if type id
	}//case
	break;

	//List Music by GENRE
	case 'L':
	{
		int count = 0;
		int numPrinted = 0;
		bool found = false;
		Music* firstMusicObj = NULL;

		//determine if their are any music objects and save the location of the first one 
		while ((count < totalItems) && (found == false))
		{
			if (typeid(*(items[count])) == typeid(Music))
			{
				found = true;
				firstMusicObj = (Music*)items[count];
			}
			count++;
		}

		//if a music was not found tell the user
		if (found == false)
		{
			std::cout << "There are no Music items to sort" << std::endl;
		}
		// if a music was found print out 
		else if (found == true)
		{
			Music::GENRE type = Music::GENRE::ROC;
			while (type != Music::GENRE::END)
			{
				std::cout << std::endl << "===== GENRE : " << (*firstMusicObj).dispGENRE(type) << " =====" << std::endl;
				count = 0;
				numPrinted = 0;
				while (count < totalItems)
				{
					if (typeid(*items[count]) == typeid(Music))
					{
						Music* music_ptr = (Music*)items[count];
						if ((*music_ptr).dispGENRESht((*music_ptr).getGENRE()) == (*music_ptr).dispGENRESht(type))
							//comparing strings to allow comparison, enums refused to compile
						{
							if (!((*music_ptr).isEmpty()))
							{
								std::cout << std::endl << "Item [" << count << "]" << std::endl;
								(*items[count]).toCout();
								numPrinted++;
							} //if isEmpty
						} //if GENRE
					} //if type id
					count++;
				}//while

				// if there were no songs of that GENRE print that out
				if (numPrinted == 0)
				{
					std::cout << "No Songs Found" << std::endl;
				} //if numPrinted

				type = Music::GENRE(type + 1);
			} //while
		} //else if

	}//case
	break;

	// display menu again menu option
	case 'M':
		print_menu();
		break;

		// enter item name_ menu option
	case 'N':
	{
		std::string new_name_;
		std::cout << "Enter Media Item Title : ";
		std::getline(std::cin, new_name_);
		(*items[ItemNum]).setName(new_name_);
	}
	break;

	// enter item page count menu option
	case 'P':
	{
		if (typeid((*items[ItemNum])) == typeid(Books))
		{
			Books* book_ptr = (Books*)items[ItemNum];

			int new_pages;
			std::cout << "Enter Media Item Pages : ";
			std::cin >> new_pages;
			(*book_ptr).setPages(new_pages);
			std::cin.ignore(10000, '\n');
		}
	}
	break;

	// quit program menu option
	case 'Q':
		done = true;
		break;

		// show memory useage
	case 'R':
	{
		std::cout
			<< std::left << std::setw(28) << "Memory Used for Authors" << " : " << sizeof(Author)*(*Authors[0]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Media Items" << " : " << sizeof(MediaItems)*(*items[60]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Book Items" << " : " << sizeof(Books)*(*items[0]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Music Items" << " : " << sizeof(Music)*(*items[20]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Video Items" << " : " << sizeof(Videos)*(*items[40]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "  Total Memory Used" << " : " <<
			(sizeof(MediaItems)*(*items[60]).in_mem()) + (sizeof(Author)*(*Authors[0]).in_mem() +
			sizeof(Books)*(*items[0]).in_mem() + sizeof(Music)*(*items[20]).in_mem() + sizeof(Videos)*(*items[40]).in_mem()) << " Bytes";

	}
	break;

	//Set Sequel index
	case 'S':
	{
		int temp_num;
		std::cout << "Enter Sequel index number : ";
		std::cin >> temp_num;
		std::cin.ignore(1, '\n');

		if (typeid(*items[ItemNum]) == typeid(Books))
		{
			Books* book_ptr = (Books*)items[ItemNum];
			Books* sql_ptr = (Books*)items[temp_num];

			(*book_ptr).setSequel(sql_ptr);
		}
		else
		{
			Videos* video_ptr = (Videos*)items[ItemNum];
			Videos* sql_ptr = (Videos*)items[temp_num];

			(*video_ptr).setSequel(sql_ptr);
		}

	}
	break;

	//Set author pointer
	case 'T':
	{
		int temp_num;
		std::cout << "Enter Author index number : ";
		std::cin >> temp_num;
		std::cin.ignore(1, '\n');
		(*items[ItemNum]).setAuthor(Authors[temp_num]);
	}
	break;



	// set the item value ($)
	case 'V':
	{
		double new_price;
		std::cout << "Enter Media Item value : ";
		std::cin >> new_price;
		std::cin.ignore(10000, '\n');
		(*items[ItemNum]).setPrice(new_price);
	}
	break;

	// set the item publication year
	case 'Y':
	{
		int new_year;
		std::cout << "Enter Media Item publication year : ";
		std::cin >> new_year;
		std::cin.ignore(10000, '\n');
		(*items[ItemNum]).setPubYear(new_year);
	}
	break;

	// default option if wrong key entered
	default:
		std::cout << "Please select an option from the menu" << std::endl << "to see the menu again type 'm'";
		break;
	}
}

//Print Menu Function
void print_menu()
{
	std::cout << std::endl
		<< "00 - 19 : Books" << std::endl
		<< "20 - 39 : Music" << std::endl
		<< "40 - 59 : Videos" << std::endl
		<< "60 - 79 : Media Items" << std::endl
		<< "*-Display data for all Media Items" << std::endl
		<< "+/ -Increment / Decrement the selected Item w / in Array" << std::endl
		<< "# Set the selected Media Item" << std::endl
		<< "0 - Clear selected Media Item data" << std::endl
		<< "B - set Media Item duration / time" << std::endl
		<< "C - Create author" << std::endl
		<< "D - Display selected Media Item data" << std::endl
		<< "E - Add Media Item element" << std::endl
		<< "F - Set Music / Video Producer / director respectively" << std::endl
		<< "J - Set Book ISBN" << std::endl
		<< "K - set Music Genre" << std::endl
		<< "L - Display Music Items by Genre" << std::endl
		<< "M - Print this menu" << std::endl
		<< "N - Set Media Item name_" << std::endl
		<< "Q - Quit this program" << std::endl
		<< "P - Set Media Item pages" << std::endl
		<< "R - Display program memory usage" << std::endl
		<< "S - Set Media Item Sequel from Index" << std::endl
		<< "T - Set Media Item Author Index" << std::endl
		<< "I - Set Media Item In Print Status(0 / 1)" << std::endl
		<< "V - Set Media Item Value" << std::endl
		<< "Y - Set Media Item Year Produced" << std::endl << std::endl;
}