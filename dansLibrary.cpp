/*------------------------------------------------------------------------------
-- Program name: CS162
-- Author: Daniel Negovan
-- Date: Winter 2019
-- Description: These are helper functions for validation, formatting etc, that
I plan to use throughout the course.
------------------------------------------------------------------------------*/

#include "dansLibrary.hpp"
#include <time.h>

const int LARGE_NUMBER = 100000;


/*-----------------------------------------------------------------------------
Prompts the user for a string until one with letters only is received, removes
anything entered after the string from the buffer, then returns the string.
------------------------------------------------------------------------------*/
std::string getLetters()
{
    std::string input;

	while(true)
    {
        bool check = true;
		std::getline(std::cin, input); //get string input

        //make sure they only entered letters
        for (unsigned int i = 0; i < input.size(); i++)
        {
            if (!isalpha(input[i]))
            {
                check = false;
            }
        }
        if (!check)
        {
            std::cout << "Please enter letters only.  Try again:" << std::endl;
        }
        else
        {
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max());
            return input;
        }

		std::cin.clear();
	}
}
/*-----------------------------------------------------------------------------
Prompts the user with a prompt that asks for for y or n until one is received,
removes anything entered after the string from the buffer, then returns the char.
------------------------------------------------------------------------------*/
char getYesNo(std::string prompt)
{
    std::cout << prompt << std::endl;
    char yesOrNo;
	std::cin >> yesOrNo;
    std::cin.clear();
    std::cin.ignore(LARGE_NUMBER, '\n');

	yesOrNo = toupper(yesOrNo);

	while (yesOrNo != 'Y' && yesOrNo != 'N')
	{
		std::cout << "Invalid input, please enter [y/n]: ";
		std::cin >> yesOrNo;
        std::cin.clear();
        std::cin.ignore(LARGE_NUMBER, '\n');
		yesOrNo = toupper(yesOrNo);
	}

    return yesOrNo;
}

/*-----------------------------------------------------------------------------
Prompts the user for an integer until one is received, removes
anything entered after the integer from the buffer, then returns the integer.
------------------------------------------------------------------------------*/
int getInteger()
{
    int input;
	std::string stringNumber;

    while(true)
	{
        std::getline(std::cin, stringNumber); //get string input
		std::stringstream convert(stringNumber); //turns the string into stream

		if(convert >> input) //Try to convert to a number
		{
			std::string leftovers;
			std::getline(convert,leftovers); //Reads the rest from the input

			if(leftovers == "") //If leftovers is empty, we have a correct number
			{
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max());
				return input;
			}
            else
            {
				std::cout << "Please enter a valid integer." << std::endl;
			}
		}
        else
        {
			std::cout << "Please enter a valid integer." << std::endl;
		}
	}
}

/*-----------------------------------------------------------------------------
Prompts the user with strign argument for an integer until one is received, removes
anything entered after the integer from the buffer, then returns the integer.
------------------------------------------------------------------------------*/
int getInteger(std::string prompt)
{
    int input;
	std::string stringNumber;

    std::cout << prompt << std::endl;

    while(true)
	{
        std::getline(std::cin, stringNumber); //get string input
		std::stringstream convert(stringNumber); //turns the string into stream

		if(convert >> input) //Try to convert to a number
		{
			std::string leftovers;
			std::getline(convert,leftovers); //Reads the rest from the input

			if(leftovers == "") //If leftovers is empty, we have a correct number
			{
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max());
				return input;
			}
            else
            {
				std::cout << "Please enter a valid integer." << std::endl;
			}
		}
        else
        {
			std::cout << "Please enter a valid integer." << std::endl;
		}
	}
}


/*-----------------------------------------------------------------------------
Prompts the user for a double until one is received, removes
anything entered after the double from the buffer, then returns the double.
------------------------------------------------------------------------------*/
double getDouble()
{
    double input;

	while(true)
    {
        if (std::cin >> input)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        else
        {
            std::cerr << "Please enter a valid number."  << std::endl;
            std::cin.clear(); //in case an error occurs with cin
            while (std::cin.get() != '\n');  //empty loop
        }

	}

}


/*-----------------------------------------------------------------------------
Prompts the user with a provided string argument, and validates
that the user enters an int, then checks that the int is between the provided
min and max arguments (inclusive).
------------------------------------------------------------------------------*/
int getIntWithinRange(std::string prompt, int min, int max)
{

    std::cout << prompt
              //<< " Choose a number from " << min << " to " << max << "."
              << std::endl;
    int input = getInteger();

    //validate range
    while(input < min || input > max)
    {
        std::cout << "Out of range. Choose a number from " << min << " to "
                  << max << "." << std::endl;

        input = getInteger();
    }
    return input;
}

/*-----------------------------------------------------------------------------
Prompts the user with a provided string argument, and validates
that the user enters a double, then checks that it is between the provided
min and max arguments (inclusive).
------------------------------------------------------------------------------*/
double getDoubleWithinRange(std::string prompt, double min, double max)
{

    std::cout << prompt << " Choose a number from " << min << " to "
              << max << std::endl;
    double input= getDouble();

    //validate range
    while(input < min || input > max)
    {
        std::cout << "Out of range. Choose a number from " << min << " to "
                  << max << std::endl;

        input = getDouble();
    }
    return input;
}


/*-----------------------------------------------------------------------------
Prompts the user with a provided string argument, and validates
that the user enters a double, then checks that the it is between the provided
min and max arguments (inclusive).
------------------------------------------------------------------------------*/
double getMoneyWithinRange(std::string prompt, double min, double max)
{
    bool isMoney = true;

    std::cout << prompt << " Choose an amount from $" << makeTwoDecimals(min)
              << " to $" << makeTwoDecimals(max) << std::endl;
    double input = getDouble();

    //check that they only entered 2 numbers after decimal
    double check1 = input * 100;
    int check2 = check1;
    if (check1 != check2)
    {
        isMoney = false;
        std::cout << "Please enter a valid monetary value in USD."
                  << std::endl;
    }

    //validate range
    while(input < min || input > max || !isMoney)
    {
        std::cout << "Choose an amount from $" << makeTwoDecimals(min)
                  << " to $" << makeTwoDecimals(max) << std::endl;

        input = getDouble();

        //check that they only entered 2 numbers after decimal
        double check1 = input * 100;
        int check2 = check1;
        if (check1 != check2)
        {
            isMoney = false;
            std::cout << "Please enter a valid monetary value in USD."
                      << std::endl;
        }
        else
        {
            isMoney = true;
        }
    }

    return input;
}


/*-----------------------------------------------------------------------------
Prompts the user for a file name to read, takes a string, and uses provided
ifsteam argument to open file for reading.  Prompts again if open fails.
------------------------------------------------------------------------------*/
void promptOpenRead(std::ifstream& inputFile)
{
    std::string inFileName;
    do
    {
        std::cout << "What is the name of the file you'd like to read?"
                  << std::endl;
        std::cin >> inFileName;

        inputFile.open(inFileName);

        if(inputFile.fail())
        {
            std::cout << "File not found." << std::endl;
        }
    }
    while(inputFile.fail());
}


/*-----------------------------------------------------------------------------
Prompts the user for a file name to write to, takes a string, and uses provided
ofsteam argument to open file for writing.  Prompts again if open fails.
------------------------------------------------------------------------------*/
void promptOpenWrite(std::ofstream& outputFile)
{
    std::string outFileName;
    do {
        std::cout << "What will be the name of your output file?" << std::endl;
        std::cin >> outFileName;

        outputFile.open(outFileName);

        if(outputFile.fail())
        {
            std::cout << "There was an error opening the output file."
                      << std::endl;
        }
    } while(outputFile.fail());
}


/*-----------------------------------------------------------------------------
Converts double to a string with 2 decimal point values and commas for thousands
------------------------------------------------------------------------------*/
std::string makeTwoDecimals(double value)
{
    std::ostringstream stream;
    std::string money;

    stream << std::setprecision(2) << std::fixed << value;
    money = stream.str();

    int insertPosition = money.length() - 6;
    while (insertPosition > 0)
    {
        money.insert(insertPosition, ",");
        insertPosition-=3;
    }

    return money;
}


/*-----------------------------------------------------------------------------
Converts int to string and adds commas for output formatting
------------------------------------------------------------------------------*/
std::string addCommas (int value)
{
    std::ostringstream stream;
    std::string number;

    stream << value;
    number = stream.str();

    int insertPosition = number.length() - 3;
    while (insertPosition > 0)
    {
        number.insert(insertPosition, ",");
        insertPosition-=3;
    }

    return number;
}


/*-----------------------------------------------------------------------------
prints the contents of the provided file name in the provided color
uses LINE WIDTH from formatting hpp
------------------------------------------------------------------------------*/
void printFile(std::string fileName, std::string color, double seconds)
{
    //open file
    std::ifstream stream(fileName, std::ios::in);

    //keep a character count, newline if we hit the line width global const
    int counter = 0;

    std::cout << color;
    std::string contents;

    //grab each line
    while(getline(stream, contents))
    {
        if (contents.empty())
        {
            counter = 0;
        }
        std::string temp;
        std::stringstream ss;

        //put each line into stream
        ss << contents;
        while (!ss.eof())
        {
            //put each word into string
            ss >> temp;
            counter += temp.size();
            if (counter < LINE_WIDTH)
            {
                std::cout << temp;
            }
            if (counter >= LINE_WIDTH)
            {
                //wait given seconds to print next line
                wait(seconds);
                std::cout << "\n" << temp;
                counter = 0;
                counter += temp.size();
            }
            //put the space back in
            std::cout << " ";
        }

        ss.clear();
        //wait a bit between lines
        wait(seconds/2);
        std::cout << "\n";
        counter = 0;
    }

    // a bit at the end for drama!
    wait(seconds);

    std::cout << RESET;
    stream.close();

}


/*-----------------------------------------------------------------------------
prints the contents of the provided string in the provided color
uses LINE WIDTH from formatting hpp, waits provided seconds between lines
------------------------------------------------------------------------------*/
void printString(std::string str, std::string color, double seconds)
{
    std::stringstream ss;
    std::string temp;
    int counter = 0;

    ss << str;

    std::cout << color;

    //read full string
    while (!ss.eof())
    {
        //keep a character count, newline if we hit the end
        ss >> temp;  //goes until it hits a space
        counter += temp.size();
        if (counter < LINE_WIDTH)
        {
            //print the word
            std::cout << temp;
        }
        if (counter >= LINE_WIDTH)
        {
            //wait to print next line, for drama purposes
            wait(seconds);
            //newline, then the word
            std::cout << "\n" << temp;
            //reset counter for next line
            counter = 0;
            counter += temp.size();
        }
        //put the space back in
        std::cout << " ";
    }

    ss.clear();
    //newline at end of this function needs to wait, too, for consistency
    wait(seconds);
    std::cout << "\n" << RESET << std::endl;

}

/*-----------------------------------------------------------------------------
creates a pause in the terminal output
------------------------------------------------------------------------------*/
void wait(double seconds)
{
    clock_t wait;

    wait = clock();
    while (clock() <= wait + (seconds * CLOCKS_PER_SEC));

}
