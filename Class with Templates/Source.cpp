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
#endif

//User Defined Class Includes
#include "Author.hpp"
#include "Elements.hpp"
#include "MediaItems.hpp"
#include "Books.hpp"
#include "Music.hpp"
#include "Videos.hpp"


//Gloabal Variables and Defines
#define OBJS_MI 80 //number of Media Items
#define PER_GROUP 20
#define OBJS_AUTH 8 //number of Authors
#define TEXT_WIDTH 20
bool done = false;

//determine if interactive or scripted
int interactive = _isatty(_fileno(stdin)); //windowns statement
//int interactive = isatty(STDIN_FILENO); //unix statement

//define global pointers for media item objects
MediaItems* mixed_array[OBJS_MI];
int ItemNum = 0;
//

//define global pointers for author objects
Author* Auth_ptr;
int* AuthNum_ptr;
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
	//Create an array, of size OBJS_AUTH of author items for filling with data
	//useing the global pointer we can use the item specified with 
	int AuthNum = 0;
	AuthNum_ptr = &AuthNum;
	Author Authors[OBJS_AUTH];
	Auth_ptr = &Authors[*AuthNum_ptr];

	//create array of items
	init_mixed_array();

	mixed_array[ItemNum];


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
		while (count <= (OBJS_AUTH - 1))
		{
			if (Auth_ptr[count].isEmpty());
			//isempty() returns the hasData value which is false for an object with no data and true for an object with data, hence the ! to invert the return value
			else
			{
				std::cout << std::endl << "Author [" << count << "] :" << std::endl;
				Auth_ptr[count].toCout();
			}
			count++;
		}

		std::cout << std::endl << std::endl << std::left << std::setw(TEXT_WIDTH) << "  Authors in Memory" << " : " << Auth_ptr[0].in_mem() << std::endl
			<< std::left << std::setw(TEXT_WIDTH) << "    Memory Used" << " : " << sizeof(Author)*Auth_ptr[0].in_mem() << " Bytes";

		std::cout << std::endl << "===== All Authors End =====" << std::endl;

		//Print out all Media Item Objects
		std::cout << std::endl << std::endl << "===== All Items Start =====" << std::endl;
		count = 0;
		while (count <= (OBJS_MI - 1))
		{
			if ((*mixed_array[count]).isEmpty());
			else //if (mixed_array[count].isEmpty() == true)
			{
				std::cout << std::endl << "Item [" << count << "]" << std::endl;
				(*mixed_array[count]).toCout();
			}
			count++;
		}

		std::cout << std::endl << std::endl << std::left << std::setw(TEXT_WIDTH) << "  Items in Memory" << " : " << (*mixed_array[0]).in_mem() << std::endl
			<< std::left << std::setw(TEXT_WIDTH) << "    Memory Used" << " : " << sizeof(MediaItems)*(*mixed_array[0]).in_mem() << " Bytes";

		std::cout << std::endl << "====== All Items End ======" << std::endl;

		std::cout << std::endl << std::left << std::setw(TEXT_WIDTH) << "  Total Memory Used" << " : " << (sizeof(MediaItems)*(*mixed_array[0]).in_mem()) + (sizeof(Author)*Auth_ptr[0].in_mem()) << " Bytes";
	}
	break;

	//increase item number by 1
	case '+':
	{
		if (ItemNum < (OBJS_MI - 1))
		{
			ItemNum = ItemNum + 1;
		}
		else if (ItemNum >= (OBJS_MI - 1))
		{
			ItemNum = (OBJS_MI - 1);
		}
		std::cout << std::endl;
	}
	break;

	//decrease item number by 1
	case '-':
	{
		if (ItemNum > 0)
		{
			ItemNum = ItemNum - 1;
		}
		else if (ItemNum <= 0)
		{
			ItemNum = 0;
		}
		std::cout << std::endl;
	}
	break;

	// set a custom item number between 0-OBJS_MI
	case '#':
	{
		//declare temp vaiable and read in user value
		int new_itemNum;
		std::cout << "Enter new item number : ";
		std::cin >> new_itemNum;

		//validate input
		if ((new_itemNum >= 0) && (new_itemNum <= (OBJS_MI - 1)))
		{
			ItemNum = new_itemNum;
		}
		else{
			std::cout << "Please enter a valid number beteen 0-" << OBJS_MI;
		}

		//clear buffer for next input
		std::cin.ignore(10000, '\n');
		std::cout << std::endl;
	}
	break;

	// clear item menu option
	case '0':
	{
		(*(mixed_array[ItemNum])).clear();
		std::cout << "Item " << ItemNum << " Cleared" << std::endl;
	}
	break;

	//set media item duration or time
	case 'B':
	{
		if (!(typeid(*mixed_array[ItemNum]) == typeid(Books) || typeid(*mixed_array[ItemNum]) == typeid(MediaItems)))
		{
			double runTime;
			std::cout << "Please enter the run time : ";
			std::cin >> runTime;
			if (typeid(*mixed_array[ItemNum]) == typeid(Music))
			{
				Music* music_ptr = (Music*)mixed_array[ItemNum];
				(*music_ptr).setRunTime(runTime);
			}
			else
			{
				Videos* video_ptr = (Videos*)mixed_array[ItemNum];
				(*video_ptr).setRunTime(runTime);
			}

		}
		else
		{
			std::cout << "Error : you cannot set the runtime on a Book or Media Item object" << std::endl;
		}
	}
	break;

	//Create an author object
	case 'C':
	{
		int born, died;
		std::string name;

		if (interactive)
		{
			std::cout << "Please enter the Authors name :";
			std::getline(std::cin, name);
			Auth_ptr[*AuthNum_ptr].setName(name);


			std::cout << "Please enter the Authors birth year (yyyy), Zero(0) for none :";
			std::cin >> born;
			Auth_ptr[*AuthNum_ptr].setBirth(born);
			std::cin.ignore(10000, '\n');

			std::cout << "Please enter the Authors death year (yyyy), Zero(0) for none :";
			std::cin >> died;
			Auth_ptr[*AuthNum_ptr].setDeath(died);
			std::cin.ignore(10000, '\n');

			*AuthNum_ptr = *AuthNum_ptr + 1;
		}
		else //scripted
		{
			std::cin >> Auth_ptr[*AuthNum_ptr];
			//std::cin.ignore(256, '\n');

			*AuthNum_ptr = *AuthNum_ptr + 1;
		}
	}
	break;

	// display item menu option
	case 'D':
	{
		std::cout << std::endl << "Item [" << ItemNum << "] :" << std::endl;
		(*mixed_array[ItemNum]).toCout();
	}
	break;

	//Create an element object in the media item object
	case 'E':
	{
		int num, start, end;
		std::string name;

		if (interactive)
		{
			std::cout << "Please enter the Element name : ";
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
			Auth_ptr[*AuthNum_ptr].setName(name);
		}


		(*mixed_array[ItemNum]).setElement(start, end, name, num = 0);

	}
	break;

	//set music/video producer/director respectivly
	case 'F':
	{
		if (!(typeid(*mixed_array[ItemNum]) == typeid(Books) || typeid(*mixed_array[ItemNum]) == typeid(MediaItems)))
		{
			std::string executive;
			std::cout << "Please enter the Producer or Director : ";
			std::getline(std::cin, executive);


			if (typeid(*mixed_array[ItemNum]) == typeid(Music))
			{
				//create a simple variable that points to cast version of the object
				Music* music_ptr = (Music*)mixed_array[ItemNum];
				//set the producer
				(*music_ptr).setExecutive(executive);
			}
			else
			{
				//create a simple variable that points to cast version of the object
				Videos* video_ptr = (Videos*)mixed_array[ItemNum];
				//set the director
				(*video_ptr).setExecutive(executive);
			}
		}
		else
		{
			std::cout << "Error : you cannot set the producer or director on a Book or Media Item object" << std::endl;
		}
	}
	break;

	// set the item in print status
	case 'I':
	{
		if (typeid(*mixed_array[ItemNum]) == typeid(Books))
		{
			//create a simple variable that points to cast version of the object
			Books* book_ptr = (Books*)mixed_array[ItemNum];

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
		if (typeid(*mixed_array[ItemNum]) == typeid(Books))
		{
			//create a simple variable that points to cast version of the object
			Books* book_ptr = (Books*)mixed_array[ItemNum];

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

	//set Music genre
	case 'K':
	{
		if (typeid(*mixed_array[ItemNum]) == typeid(Music))
		{
			//create a simple variable that points to cast version of the object
			Music* music_ptr = (Music*)mixed_array[ItemNum];

			//get the genre string from input
			std::string genreStr;
			std::cout << "Please enter the Genre : ";
			std::getline(std::cin, genreStr);
			for (auto & c : genreStr) c = toupper(c); //convert to uppercase

			//create a bool variable to determine if the genre has been set
			bool genreSet = false;

			//variable to keep track of type
			Music::Genre type = Music::Genre::ROC;

			//for loop to try find a match to one of the defined genres
			while ((type != Music::Genre::END) && (genreSet == false))
			{
				//get the token for searching the genre string
				std::string typeStr = (*music_ptr).dispGenreSht(type);

				//if the token matches something in the genre string set the object to the genre
				if (genreStr.find(typeStr) != std::string::npos)
				{
					(*music_ptr).setGenre(type);
					genreSet = true;
				} //if genreStr
				type = Music::Genre(type + 1);
			}//while
			if (genreSet == false)
			{
				(*music_ptr).setGenre(Music::Genre::OTHER);
			}
		} //if type id
	}//case
	break;

	//List Music by genre
	case 'L':
	{
		int count = 0;
		int numPrinted = 0;
		bool found = false;
		Music* firstMusicObj = NULL;

		//determine if their are any music objects and save the location of the first one 
		while ((count < OBJS_MI) && (found == false))
		{
			if (typeid(*(mixed_array[count])) == typeid(Music))
			{
				found = true;
				firstMusicObj = (Music*)mixed_array[count];
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
			Music::Genre type = Music::Genre::ROC;
			while (type != Music::Genre::END)
			{
				std::cout << std::endl << "===== Genre : " << (*firstMusicObj).dispGenre(type) << " =====" << std::endl;
				count = 0;
				numPrinted = 0;
				while (count < OBJS_MI)
				{
					if (typeid(*mixed_array[count]) == typeid(Music))
					{
						Music* music_ptr = (Music*)mixed_array[count];
						if ((*music_ptr).dispGenreSht((*music_ptr).getGenre()) == (*music_ptr).dispGenreSht(type))
						//comparing strings to allow comparison, enums refused to compile
						{
							if (!((*music_ptr).isEmpty()))
							{
								std::cout << std::endl << "Item [" << count << "]" << std::endl;
								(*mixed_array[count]).toCout();
								numPrinted++;
							} //if isEmpty
						} //if genre
					} //if type id
					count++;
				}//while

				// if there were no songs of that genre print that out
				if (numPrinted == 0)
				{
					std::cout << "No Songs Found" << std::endl;
				} //if numPrinted

				type = Music::Genre(type + 1);
			} //while
		} //else if

	}//case
	break;

	// display menu again menu option
	case 'M':
		print_menu();
		break;

		// enter item name menu option
	case 'N':
	{
		std::string new_name;
		std::cout << "Enter Media Item Title : ";
		std::getline(std::cin, new_name);
		(*mixed_array[ItemNum]).setName(new_name);
	}
	break;

	// enter item page count menu option
	case 'P':
	{
		if (typeid((*mixed_array[ItemNum])) == typeid(Books))
		{
			Books* book_ptr = (Books*)mixed_array[ItemNum];

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
			<< std::left << std::setw(28) << "Memory Used for Authors" << " : " << sizeof(Author)*Auth_ptr[0].in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Media Items" << " : " << sizeof(MediaItems)*(*mixed_array[60]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Book Items" << " : " << sizeof(Books)*(*mixed_array[0]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Music Items" << " : " << sizeof(Music)*(*mixed_array[20]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "Memory Used for Video Items" << " : " << sizeof(Videos)*(*mixed_array[40]).in_mem() << " Bytes"
			<< std::endl << std::left << std::setw(28) << "  Total Memory Used" << " : " <<
			(sizeof(MediaItems)*(*mixed_array[60]).in_mem()) + (sizeof(Author)*Auth_ptr[0].in_mem() +
			sizeof(Books)*(*mixed_array[0]).in_mem() + sizeof(Music)*(*mixed_array[20]).in_mem() + sizeof(Videos)*(*mixed_array[40]).in_mem()) << " Bytes";

	}
	break;

	//Set Sequel index
	case 'S':
	{
		int temp_num;
		std::cout << "Enter Sequel index number : ";
		std::cin >> temp_num;
		std::cin.ignore(1, '\n');

		if (typeid(*mixed_array[ItemNum]) == typeid(Books))
		{
			Books* book_ptr = (Books*)mixed_array[ItemNum];
			Books* sql_ptr = (Books*)mixed_array[temp_num];

			(*book_ptr).setSequel(sql_ptr);
		}
		else
		{
			Videos* video_ptr = (Videos*)mixed_array[ItemNum];
			Videos* sql_ptr = (Videos*)mixed_array[temp_num];

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
		(*mixed_array[ItemNum]).setAuthor(&Auth_ptr[temp_num]);
	}
	break;



	// set the item value ($)
	case 'V':
	{
		double new_price;
		std::cout << "Enter Media Item value : ";
		std::cin >> new_price;
		std::cin.ignore(10000, '\n');
		(*mixed_array[ItemNum]).setPrice(new_price);
	}
	break;

	// set the item publication year
	case 'Y':
	{
		int new_year;
		std::cout << "Enter Media Item publication year : ";
		std::cin >> new_year;
		std::cin.ignore(10000, '\n');
		(*mixed_array[ItemNum]).setPubYear(new_year);
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
		<< "F - Set Music / Video Producer / Director respectively" << std::endl
		<< "J - Set Book ISBN" << std::endl
		<< "K - set Music Genre" << std::endl
		<< "L - Display Music Items by Genre" << std::endl
		<< "M - Print this menu" << std::endl
		<< "N - Set Media Item name" << std::endl
		<< "Q - Quit this program" << std::endl
		<< "P - Set Media Item pages" << std::endl
		<< "R - Display program memory usage" << std::endl
		<< "S - Set Media Item Sequel from Index" << std::endl
		<< "T - Set Media Item Author Index" << std::endl
		<< "I - Set Media Item In Print Status(0 / 1)" << std::endl
		<< "V - Set Media Item Value" << std::endl
		<< "Y - Set Media Item Year Produced" << std::endl << std::endl;
}

int init_mixed_array()
{
	for (int i = 0; i < OBJS_MI; i++)
	{
		int type = (i / (PER_GROUP));
		//-------
		switch (type)
		{
		case 0:
			mixed_array[i] = new Books();
			break;

		case 1:
			mixed_array[i] = new Music();
			break;

		case 2:
			mixed_array[i] = new Videos();
			break;

		case 3:
			mixed_array[i] = new MediaItems();
			break;

		default:
			std::cout << "ERROR : in array initialize" << std::endl;
			return -1;
		}
	}
	return 0;
}