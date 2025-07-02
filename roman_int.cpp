#include "std_lib_facilities.h"
#include "roman_int.h"

int return_offset(const int numb)
{	
	// This unique function determines how we should offset the given integer index for the process int function below. 
	// Returns the correct offset to determine subtractive value check. 
	
	// This is working on an iterative index (numb)
	if (numb == 0)
	{
		return 0;
	}
	else if (numb % 2 == 0)
	{
		// If even drop down the table by 2.
		return int_tbl[numb-2];
	}
	else if (numb % 2 != 0)
	{
		// If odd drop by 1
		return int_tbl[numb-1]; 
	}
}

string process_int(int numb)
{	
	// Processes an integer into a correct numeral string
	// Intended to work on the least expendable form of an integer, that is 1,10s,100s etc. 
	string numeral = "";
	string buffer = "";

	while (numb != 0)
	{	
		// Iterate through the available roman numeral values. 
		for (int i = int_tbl.size() - 1; i >= 0; --i)
		{	 
			// Check for match. // This is an important piece of math for the entire program to function effectively. Critical line. 
			if (int_tbl[i] <= numb || int_tbl[i] - return_offset(i) == numb)
			{	
				// If match update the number
				numb -= int_tbl[i]; 

				// If number is now negative, we have a subtractive case. 
				if (numb < 0)
				{	
					// Store the offset in a buffer for later.
					// Now reset the negative value to its absolute value. 
					buffer += to_string(char_tbl[i]);
					numb = abs(numb);
				}
				else if (numb >= 0)
				{	
					// Standard cases update as usual. 
					numeral += to_string(char_tbl[i]);
				}
				++i; // reset
			}
		}
	}
	return (numeral + buffer); 
}

string int_to_roman(int numb)
{
	// Breaks an integer number into least expendable form.
	// Then processes and returns this value. 

	// First we need to get the number into least expendable form. 
	int original = numb; 
	vector<int> values;
	string numerals; 

	int thousands = (numb / 1000) * 1000; 
	values.push_back(thousands);

	numb -= thousands; 

	int hundreds = (numb / 100) * 100;
	values.push_back(hundreds);

	numb -= hundreds;

	int tens = (numb / 10) * 10;
	values.push_back(tens);
	numb -= tens;

	int ones = (numb / 1); 
	values.push_back(ones);

	// Now perform the algorithm on each piece, and add them together.
	for (int n : values)
	{
		if (n > 0)
		{	
			string s = process_int(n);
			numerals += s; 
		}
	}
	return numerals; 
}

int sub_check(int total, int lv, int result)
{	
	// Take in the total value of the numeral as calculated thus far.
	// The value of the lest character in the subtraction.
	// The result of the subtraction in question. 

	const vector<int> valid_vals{ 1, 10, 100 };
	bool valid = false;
	const int offset = 10;

	for (int v : valid_vals)
	{
		// First make sure the left value is correct.
		// A simple check. 
		if (lv == v)
		{
			valid = true;
		}
	}

	// A unique method of error checking.
	// CURRENT TOTAL mod [10*left_val] = subtraction result
	// If the result matches this formula its valid, else its not a valid subtraction. 
	int calculation = total % (offset * lv);

	// If the calculation is valid return. 
	if (calculation == result && valid)
	{	
		return total;
	}
	else
	{	
		return -1;
	}
}

int roman_to_int(const string s)
{	
	// Converts a given roman numeral to valid integer.
	// -1 denotes invalid string.

	int total = 0; 
	int count = 1; // Counts repeating elements
	int buffer = 9999; // start at 9999, no numeral can be bigger than this.
	char last_element = 'z';
	const vector<char> repeats = { 'V', 'L', 'D' }; 
	vector<int> flags = { 1, 1, 1 }; 
	int last_val = 99999; // Store last value in case of subtraction. 

	if (s.empty())
	{	
		// Invalid
		return -1; 
	}

	for (char c : s)
	{	
		// Obtain the value. 
		int value = validate_char(c, repeats, flags);

		// First check for repeat elements and reset accordingly. 
		if (c == last_element)
		{
			++count;
		}
		else if (c != last_element)
		{	
			// reset count; 
			count = 1;
		}

		if (value == -1 || count > 3)
		{
			// invalid
			return -1; 
		}
		else if (value > buffer)
		{	
			last_val = buffer; 
			// subract and update total using method
			// update buffer
			int result = (value - buffer);
			total -= buffer; // remove the last buffer value; 
			total += result; // replace it with the result. 
			total = sub_check(total, buffer, result); 
			buffer = result; 
			last_element = c; 
		}
		else if (value <= buffer && value < last_val) // apply the rule of subtractive decent [LV RV NEW] then NEW < LV 
		{	
			total += value; 
			buffer = value; 
			last_element = c; 
		}
		else
		{
			return -1; 
		}
	}
	return total;  
}

int validate_char(const char c, vector<char> repeats, vector<int>& flags)
{	
	// Check a given character for repeats, such as IIII. 
	for (int i = 0; i < repeats.size(); ++i)
	{
		if (c == repeats[i])
		{	
			if (flags[i])
			{
				// If valid
				flags[i] = 0;
			}
			else if (!flags[i])
			{
				// invalid, repeating of non repeat.
				return -1; 
			}
		}
	}

	// COnvert using table. 
	for (int i = 0; i < char_tbl.size(); ++i)
	{
		if (c == char_tbl[i])
		{
			return int_tbl[i];
		}
	}
	// -1 denotes an invalid char.
	return -1;
}

Roman_int get_roman()
{
	// Retrieve a set of characters from CIN
	// Process into a Roman_int
	
	char c; 
	int total = 0;
	int count = 1; // Counts repeating elements
	int buffer = 9999; // start at 9999, no numeral can be bigger than this. // A buffer to store previous relevant numerical values. 
	char last_element = 'z'; // Last char before current just read in. 
	vector<int> flags = { 1, 1, 1 }; // TO track special characters which only occur once (see repeats vector)

	Roman_int r; // The struct we intend to return. 

	int last_val = 99999; // This value needs to be stored in the case of a subtraction. 

	while (true)
	{
		cin >> c; 

		if (c == '=')
		{	
			// End of input
			cout << "STOP.\n"; 
			break; 
		}

		// Obtain the value and process into a valid integer 
		// Or -1 if invalid. 
		int value = validate_char(c, repeats, flags);

		// Now, check for repeating elements and reset count accordingly. 
		if (c == last_element)
		{
			++count;
		}
		else if (c != last_element)
		{
			// reset count; 
			count = 1;
		}

		// After these updates check if loop is still valid. 
		if (value == -1 || count > 3)
		{
			// invalid
			error("Invalid input."); 
		}
		// If it is perform arithmetic checks as follows
		else if (value > buffer)
		{	
			// Store the last value
			last_val = buffer; 
			// Perform the subtraction and update result
			int result = (value - buffer);
			// Update the total accordingly, while aligning the buffer.
			total -= buffer; // remove the last buffer value; 
			total += result; // replace it with the result of the subtraction. (Because we intend to subtract what would have been added (buffers last value))
			total = sub_check(total, buffer, result); // A very important error check. 
			buffer = result; // Update the buffer with validated result. 
			last_element = c; // Update last element
			r.numerals.push_back(c); // Update the numeral string. 
		}
		else if (value <= buffer && value < last_val) // apply the rule of subtractive decent [LV RV NEW] then NEW < LV 
		{
			// Most cases we add and it is simpler.
			total += value; // We update the total.
			buffer = value; // Update buffer
			last_element = c; // Update the previous char. 
			r.numerals.push_back(c); // Update numeral string. 
		}
		else
		{	
			// Fall through case, highly unlikely or impossible this would occur, but a nice safety net. 
			error("Invalid input.");
		}
	} // end while

	// Final check.
	if (total == -1)
	{	
		// We can still see the numeral, but it confirms this numeral is invalid. 
		r.numerals += "(INVALID)";
	}
	// Update the total integer value of the numeral string.
	// Return the entire struct. 
	r.value = total; 
	return r; 
}

bool is_digit(char c)
{
	// Library version wasnt working for some reason. 
	switch (c) {
	case '0':
		return true; 
		break;
	case '1':
		return true;
		break;
	case '2':
		return true;
		break;
	case '3':
		return true;
		break;
	case '4':
		return true;
		break;
	case '5':
		return true;
		break;
	case '6':
		return true;
		break;
	case '7':
		return true;
		break;
	case '8':
		return true;
		break;
	case '9':
		return true;
		break; 
	default:
		return false; 
		break;
	}
}

bool is_roman(char c)
{
	for (char numeral : char_tbl)
	{
		if (c == numeral)
		{
			return true;
		}
	}
	return false; 
}

void romanize(string& fname, string& ofname)
{
	ifstream ist{ fname };
	ofstream ost{ ofname };

	if (!ist || !ost)
	{
		error("Could not open file.\n");
	}

	string value = "";
	bool last = false; 
	for (char c; ist.get(c);)
	{
		if (is_digit(c))
		{	
			//cout << "This is a digit! " << c << "\n";
			value += c; 
			last = true; 
		}
		else if (last)
		{
			int numb = stoi(value);
	
			if (numb > 0 && numb <= 4000)
			{
				string numerals = int_to_roman(numb);
				ost << numerals << " ";
			}
			else
			{
				ost << value;
			}

			value = "";
			last = false;
		}
		else
		{
			ost << c;
		}
	}

	cout << "Success...exiting\n";
}

void deromanize(string& fname, string& ofname)
{
	ifstream ist{ fname };
	ofstream ost{ ofname };

	if (!ist || !ost)
	{
		error("Could not open file.\n");
	}

	string value = "";
	bool last = false;

	for (char c; ist.get(c);)
	{
		if (is_roman(c))
		{
			//cout << "This is a digit! " << c << "\n";
			value += c;
			last = true;
		}
		else if (last)
		{
			int numb = roman_to_int(value);

			if (numb == -1)
			{	
				// If invalid just print it back and carry on. 
				ost << value;
			}
			else
			{
				ost << numb;
			}

			ost << c; 
			value = "";
			last = false;
		}
		else
		{
			ost << c;
		}
	}

	cout << "Success...exiting\n";
}



ostream& operator<<(ostream& ost, Roman_int& r)
{
	return ost << r.numerals; 
}

Roman_int operator+(Roman_int& l, Roman_int& r)
{
	int left = l.value;
	int right = r.value;

	int v = left + right;

	string n = int_to_roman(v);

	Roman_int result;
	result .value = v;
	result.numerals = n;

	return result; 
}

Roman_int operator-(Roman_int& l, Roman_int& r)
{
	int left = l.value;
	int right = r.value;

	int v = left - right;

	string n = int_to_roman(v);

	Roman_int result;
	result.value = v;
	result.numerals = n;

	return result;
}

Roman_int operator/(Roman_int& l, Roman_int& r)
{
	int left = l.value;
	int right = r.value;

	if (right == 0)
	{
		error("Divide by zero.");
	}

	int v = left/right;

	string n = int_to_roman(v);

	Roman_int result;
	result.value = v;
	result.numerals = n;

	return result;
}

void operator--(Roman_int& l)
{
	int left = l.value;
	int v = left - 1;
	string n = int_to_roman(v);
	Roman_int result;
	result.value = v;
	result.numerals = n;

	l = result;
}

void operator++(Roman_int& l)
// Unary
{	
	int left = l.value;
	int v = left + 1;
	string n = int_to_roman(v);
	Roman_int result;
	result.value = v;
	result.numerals = n;

	l = result; 
}



//Not sure what Bjarne meant by an input operator for roman_int?
///The real question is how the compiler is supposed to recognize an input of char over an int.

//istream& operator>>(istream& ist, roman_int& r)
//{
	//return get_roman(); 

//}