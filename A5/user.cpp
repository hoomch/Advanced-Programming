#include "user.hpp"

User::User() : name(30){
	record = 0;
	score = 0;
}
int User::get_record(){
	return record;
}
int User::get_score(){
	return score;
}
void User::printNameAndRecord(Window * win , int x , int y , int number , int height , string font , int fontSize){
	string output ;
	output += int_to_string(number);
	output += ". ";
	output += name.getString();
	string rec;
	rec += int_to_string(record);
	win->show_text(output , x , y + number * height , NEAR_BLACK , font , fontSize);
	win->show_text(rec , x + 150 , y + number * height , NEAR_BLACK , font , fontSize);
}
MyString* User::get_name(){
	return &name;
}
void User::eraseName(){
	name.eraseAll();
}
string User::get_string_name(){
	return name.getString();
}
void User::set_score(int newScore){
	score = newScore;
}
void User::set_record(int newRecord){
	record = newRecord;
}