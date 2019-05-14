#ifndef BIGMAN_H
#define BIGMAN_H

#include <iostream>

#include <vector>

#include <string>

#include "Person.hpp"

class Bigman : public Person
{
	public:
		Bigman(std::string _name,std::string _role, bool _silenced, bool _extra, int _health);
};

#endif