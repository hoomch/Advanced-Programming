#include "Doctor.hpp"

using namespace std;

Doctor::Doctor(string _name,string _role, bool _silenced, bool _extra, int _health, bool is_used)
	:Person(_name, _role, _silenced, _extra, _health)
{
	already_healed = is_used;
}

void Doctor::action()
{
	already_healed = true;
}