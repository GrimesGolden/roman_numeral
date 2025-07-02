#include "std_lib_facilities.h"
#include "roman_int.h"

// Define a roman_int class for holding roman numerals as ints with a << and >>/ 
// Provide roman_int with as_int() member that returns the int value,
// So that if r is a roman_int, then we can write,
// cout << "Roman" << r << " equals " << r.as_int() << "\n;

// As it stands is only valid for 0-4000. But it is arguable the roman numeral system itself is only truly valid for these values. 

int main()
{
	try
	{	
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
	
		/*
		* Roman_int r = get_roman(); // A roman int. 
	Roman_int l = get_roman();

	cout << " Roman " << r << " equals " << r.as_int() << "\n";
	cout << " Roman " << l << " equals " << l.as_int() << "\n";

	Roman_int a = r/l;
	cout << " Roman " << a << " equals " << a.as_int() << "\n";
	++a;
	cout << " Roman " << a << " equals " << a.as_int() << "\n";
	--a;
	cout << " Roman " << a << " equals " << a.as_int() << "\n";
		*/
	// Exactly as bjarne asked. 

		string name = "input.txt";
		string oname = "output.txt";
		string rname = "reversed.txt";
		string test = "test.txt";

		deromanize(test, oname);
	}
	catch (const std::exception& e)
	{
		cout << e.what(); 
	}
}