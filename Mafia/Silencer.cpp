#include "Silencer.hpp"

using namespace std;

Silencer::Silencer(string _name,string _role, bool _silenced, bool _extra, int _health, bool is_used)
	:Person(_name, _role, _silenced, _extra, _health)
{
	already_silenced = is_used;
}

void Silencer::action()
{
	already_silenced = true;	
}