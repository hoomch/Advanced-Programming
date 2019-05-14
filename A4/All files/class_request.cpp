#include "class_request.hpp"
Request::Request(string title , map<string,float> conditions){
	this->title=title;
	this->conditions=conditions;
}
map<string,float> Request::get_conditions(){
	return conditions;
}
string Request::get_title(){
	return title;
}