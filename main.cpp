#include "std_lib_facilities.h"
#include "roman_int.h"

// Define a roman_int class for holding roman numerals as ints with a << and >>/ 
// Provide roman_int with as_int() member that returns the int value,
// So that if r is a roman_int, then we can write,
// cout << "Roman" << r << " equals " << r.as_int() << "\n;


// to do

// we need to read in chars first
// now, the first char must of course be one of the main pieces....
// the subsequent chars determine the value.
// we can never count in more than three: I

// I think we should start with the fact that each roman_int holds itself as a struct. 

// COnstantly read in and add to a total.
// However, if the value is greater than the previous. Read it in and subtract the


// Notes: https://www.timeanddate.com/calendar/how-do-roman-numerals-work.html


// As it stands is only valid for 0-4000. 


void input_test()
{	
	while (true)
	{
		char c;
		cin >> c;

		if (c == '=')
		{
			cout << "Goodbye!\n";
			break; 
		}
		else
		{
			cout << "You typed " << c << " \n";
		}
	}
}

int main()
{
	try
	{	
		/*
		* for (int i = 1; i <= 101; ++i)
		{
			cout << i << " = " << int_to_roman(i) << " converted back to numerals that is : " << roman_to_int(int_to_roman(i)) << "\n"; 
		}
		*/
		vector<string> invalid_numerals = {
	"IIII",     // too many I's
	"VV",       // V cannot repeat
	"IC",       // invalid subtractive pair
	"VX",       // V cannot be a subtractor
	"XD",       // invalid tier jump
	"LL",       // L cannot repeat
	"IIV",      // double subtraction
	"IL",       // I cannot subtract from L
	"XIXIX",    // overlapping subtractive pairs
	"CMM"       // malformed 1900 (should be MCM)
		};

		vector<std::string> evil_cases = {
	"IXX",
	"IIV",
	"XXC",
	"VV",
	"IM",
	"XIXIX",
	"XD",
	"LC",
	"XXL",
	"MCMC",// bastard case 
	"VV",
	"VVVVV",
	"XVXVX",
	"XXXDXXX"
		};

		Roman_int r = get_roman();

		cout << "The numeral is " << r.numerals << " the value is " << r.value; 
	

	}
	catch (const std::exception& e)
	{
		cout << e.what(); 
	}
}