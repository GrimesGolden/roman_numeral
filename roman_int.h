#pragma once
#include "std_lib_facilities.h"

const vector<char> char_tbl{ 'I', 'V', 'X', 'L', 'C', 'D', 'M'};
const vector<int> int_tbl{ 1, 5, 10, 50, 100, 500, 1000};

struct Roman_int
{
	string numerals = ""; // empty string 
	int value = 0; // starts off at zero val. 
	int sum_check = 0; // if this ever goes past 3, then we know the roman_int itself is invalid. 

	int as_int()
	{
		return value; 
	}
};


int sub_check(int total, int lv, int result);
string int_to_roman(int numb);
int roman_to_int(const string s);
string process_int(int numb);
string reverse_string(string s);
int return_offset(const int numb);
int validate_char(const char c, vector<char> repeats, vector<int>& flags);
Roman_int process_char(const char c); 
Roman_int add_roman(Roman_int& left, Roman_int& right);
Roman_int sub_roman(Roman_int& left, Roman_int& right);
Roman_int get_roman();
ostream& operator<<(ostream& ost, Roman_int& r); 
//istream& operator>>(istream& ist, roman_int& r); 