#pragma once
#include "std_lib_facilities.h"

const vector<char> char_tbl{ 'I', 'V', 'X', 'L', 'C', 'D', 'M'};
const vector<char> repeats = { 'V', 'L', 'D' };
const vector<int> int_tbl{ 1, 5, 10, 50, 100, 500, 1000};

struct Roman_int
{
	string numerals = ""; // Represents the roman numeral
	int value = 0; // Integer value of the roman numeral, -1 INVALID 

	int as_int()
		// This function is actually pretty useless as it stands, but Bjarne demands it. 
	{
		return value; 
	}
};



bool is_digit(char c);
void romanize(string& fname, string& ofname);
void deromanize(string& fname, string& ofname);
int sub_check(int total, int lv, int result);
string int_to_roman(int numb);
int roman_to_int(const string s);
string process_int(int numb);
int return_offset(const int numb);
int validate_char(const char c, vector<char> repeats, vector<int>& flags);
Roman_int get_roman();
// Operator overloads, including calculator capability (exercise 7 chapter 10).  
ostream& operator<<(ostream& ost, Roman_int& r); 
void operator++(Roman_int& l);
void operator--(Roman_int& l);
Roman_int operator-(Roman_int& l, Roman_int& r);
Roman_int operator+(Roman_int& l, Roman_int& r);
Roman_int operator/(Roman_int& l, Roman_int& r);
//istream& operator>>(istream& ist, roman_int& r); 