#include "User.hpp"

using namespace std;

User::User(string _first, string _last, string _id, string _phone, int _money, string _type,vector<string> sale)
{
	first_name = _first;
	last_name = _last;
	user_name = _id;
	phone = _phone;
	money = _money;
	user_type = _type;
	sale_needers = sale;
}

void User::change_type(string new_user_type)
{
	user_type = new_user_type;
}

void User::add_needer(string buyer_name)
{
	sale_needers.push_back(buyer_name);
}

void User::add_money(int amount)
{
	money += amount;
}

