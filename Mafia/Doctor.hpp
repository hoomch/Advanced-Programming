#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>

#include <vector>

#include "Person.hpp"

class Doctor: public Person
{
	public:
		Doctor(std::string _name,std::string _role, bool _silenced, bool _extra, int _health, bool is_used);		
		void action();
		bool get_power_status() {return already_healed;}
		
	private:
		bool already_healed;

};

#endif