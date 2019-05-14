#ifndef __USER_H__
#define __USER_H__

#include "libraries.hpp"
#include "globalFunctions.hpp"
#include "myString.hpp"

const RGB NEAR_BLACK(40 , 40 , 40);
using namespace std;

class User{
private:
	MyString name;
	int record;
	int score;
public:
	User();
	int get_record();
	int get_score();
	void clearName();
	void printNameAndRecord(Window * win , int x , int y , int number , int height , string font , int fontSize);
	MyString* get_name();
	void eraseName();
	string get_string_name();
	void set_score(int newScore);
	void set_record(int newRecord);
};

#endif