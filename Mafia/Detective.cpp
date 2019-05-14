#include "Detective.hpp"

using namespace std;

Detective::Detective(string _name,string _role, bool _silenced, bool _extra, int _health, bool is_used)
	:Person(_name, _role, _silenced, _extra, _health)
{
	already_asked = is_used;
}

void Detective::action()
{
	already_asked = true;
}