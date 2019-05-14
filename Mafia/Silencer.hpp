#ifndef SILENCER_H
#define SILENCER_H

#include <iostream>

#include <vector>

#include <string>

#include "Person.hpp"

class Silencer : public Person
{
	public:
		Silencer(std::string _name,std::string _role, bool _silenced, bool _extra, int _health, bool is_used);
		void action();
		bool get_power_status() {return already_silenced;}

	private:
		bool already_silenced;
	
};

#endif