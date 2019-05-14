#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "libraries.hpp"
using namespace std;
class Request{
private:
	string title;
	map<string,float> conditions;
public:
	Request(string title , map<string,float> conditions);
	map<string,float> get_conditions();
	string get_title();
};

#endif