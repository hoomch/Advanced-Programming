#ifndef JOKER_H
#define JOKER_H

#include <iostream>

#include <vector>

#include <string>

#include "Person.hpp"

class Joker : public Person
{
	public:
		Joker(std::string _name,std::string _role, bool _silenced, bool _extra, int _health);
};

#endif