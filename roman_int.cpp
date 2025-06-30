#include "std_lib_facilities.h"
#include "roman_int.h"

// What we really need to do its process each char individually from the end.
// Processing a char then, becomes seeing if more input exists. 
// if so, keep going

// Another idea is to utilize the module operator to determine values of an int.

//https://www.cuemath.com/numbers/roman-numerals-1-to-1000/ // has the rules

// Remember V, L, and D cannot be repeated, they appear only once.

string reverse_string(string s)
{	
	// Reverses a string. 
	string new_str;

	for (int i = s.size() - 1; i >= 0; --i)
	{
		new_str += to_string(s[i]); 
	}

	return new_str; 
}

int return_offset(const int numb)
{	
	// This unique function determines precisely how we should offset the given integer index for the process int program below. 
	// Returns the correct offset to determine subtractive value check. 
	
	if (numb == 0)
	{
		return 0;
	}
	else if (numb % 2 == 0)
	{
		// even
		return int_tbl[numb-2];
	}
	else if (numb % 2 != 0)
	{
		return int_tbl[numb-1]; 
	}
}

string process_int(int numb)
{	
	// Processes an integer into a correct numeral string
	string numeral = "";
	string buffer = "";

	while (numb != 0)
	{	
		for (int i = int_tbl.size() - 1; i >= 0; --i)
		{	 
			// Check for match. 
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
			//cout << "processing " << n << " \n";
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

	// The tobin method of error checking
	// TOTAL mod [10*left_val] = subtraction result
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

	int last_val = 99999; /// error check, see evil case MCMC 

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
			last_val = buffer; //DEBUG
			// subract and update total using method
			// update buffer
			//cout << "Subtracting\n";
			int result = (value - buffer);
			//cout << "Result = value - buffer";
			//cout << result << " = " << value << " - " << buffer << "\n";
			total -= buffer; // remove the last buffer value; 
			total += result; // replace it with the result. 
			total = sub_check(total, buffer, result); 
			buffer = result; 
			//buffer = value; // Changing this, the buffer should hold the result now, not the value. 
			last_element = c; // DEBUG LINE
		}
		else if (value <= buffer && value < last_val) // apply the rule of subtractive decent [LV RV NEW] then NEW < LV 
		{	
			//cout << "The value " << value << " is less than last val " << last_val << "\n";
			// add to total.
			// update buffer. 
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

Roman_int process_char(const char c)
{	
	// Process a character into a roman numeral (roman_int). 
	// 
	// If valid, return a roman_int that represents this individual char.
	const int invalid = -1; 
	int val = 5; // just a placeholder for now. 
	//int val = validate_char(c); need to update this function for the function call.

	if (val == invalid)
	{
		error("Invalid reading");
	}
	else
	{
		Roman_int r;
		r.value = val; 
		r.numerals = c; 
		return r; 
	}
}

int validate_char(const char c, vector<char> repeats, vector<int>& flags)
{	
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

Roman_int add_roman(Roman_int& left, Roman_int& right)
{	
	// The standard method for combining roman numerals. 
	Roman_int new_r; 

	int new_val = left.value + right.value; 

	string new_numerals = left.numerals + right.numerals; 

	new_r.value = new_val;
	new_r.numerals = new_numerals; 

	return new_r; 

}

Roman_int sub_roman(Roman_int& left, Roman_int& right)
{
	// The standard method for combining roman numerals. 
	Roman_int new_r;

	// In this case we need to subtract, for example with "IV = 4". 
	int new_val = right.value - left.value;

	string new_numerals = left.numerals + right.numerals;

	new_r.value = new_val;
	new_r.numerals = new_numerals;

	return new_r;

}

Roman_int get_roman()
{	
	char c; 
	char next_c; 
	const int invalid = -1; 
	Roman_int r; 

	while (true)
	{	
		// Read in a value. 
		cin >> c; 

		cout << "Read in value " << c << "\n";

		if (c == stop)
		{
			cout << "Stop detected, break"; 
			cin.putback(c);
			break; 
		}

		r = process_char(c);

		cin >> next_c; 
		cout << "Read in next value " << next_c << "\n";

		if (next_c == stop)
		{
			cout << "Break detected due to next_c\n";
			cin.putback(next_c);
			break; 
		}

		cin.putback(next_c);
		cout << "Put back " << next_c << "\n"; 

		Roman_int next = get_roman(); 

		if ((next.value - r.value) <= 1)
		{
			// add.
			r = add_roman(r, next);
		}
		else if ((next.value - r.value) > 2)
		{
			// subt 
			// This is your problem, your subtraction rules are wrong.
			// If you had subtraction rules correct then IIV wouldnt work
			// because this is 4-1, an invalid sub. 
			// I quote "You can subtract ? from ? (5) and ? (10) but never from ? (100)" 
			// "To write 99, you have to subtract 10 from 100 (??) and add the subtraction of 1 from 10 (?)" 
			r = sub_roman(r, next);
		}
		else if ((next.value - r.value) == 2)
		{
			error("Invalid numeral.");
		}
		// END END END
	}
	// Outside of while
	return r; 
}

ostream& operator<<(ostream& ost, Roman_int& r)
{
	// Temporary for now. 
	return ost; 
}

/*
Not sure what Bjarne meant by an input operator for roman_int?
The real question is how the compiler is supposed to recognize an input of char over an int.

istream& operator>>(istream& ist, roman_int& r)
{
	// Input a roman_int

}
*/