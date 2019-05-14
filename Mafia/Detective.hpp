#ifndef DETECTIVE_H
#define DETECTIVE_H

#include <iostream>

#include <vector>

#include <string>

#include "Person.hpp"

class Detective : public Person
{
	public:
		Detective(std::string _name,std::string _role, bool _silenced, bool _extra, int _health, bool is_used);
		void action();
		bool get_power_status() {return already_asked;}

	private:
		bool already_asked;
};



#endif