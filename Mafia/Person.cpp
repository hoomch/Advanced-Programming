#include "Person.hpp"

using namespace std;

Person::Person(string _name,string _role, bool _silenced, bool _extra, int _health)
{
	name = _name;
	role = _role;
	is_silenced = _silenced;
	is_healed = _extra;
	health = _health;
}

void Person::action()
{

}

void Person::add_role(string role_name)
{
	role = role_name;
}

void Person::add_protection()
{
	is_healed = true;
}

void Person::kill_person()
{
	health --;
}

void Person::make_silent()
{
	is_silenced = true;
}

void Person::reset()
{
	is_silenced = false;
	is_healed = false;
}
