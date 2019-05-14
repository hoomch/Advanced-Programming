#ifndef USER_H
#define USER_H

#include <iostream>

#include <vector>

class User
{
	private:
		std::string first_name,last_name,user_name,phone,user_type;
		std::vector<std::string> sale_needers;
		int money;
	public:
		User(std::string _first, std::string _last, std::string _id, std::string _phone,
			 int _money,std::string _type, std::vector<std::string> sale);
		std::string get_id() {return user_name;}
		std::string get_first_name() {return first_name;}
		std::string get_last_name() {return last_name;}
		std::string get_phone() {return phone;}
		std::string get_type() {return user_type;}
		std::vector<std::string> get_needers() {return sale_needers;}
		int get_money() {return money;}
		void change_type(std::string new_user_type);
		void add_needer(std::string buyer_name);
		void add_money(int amount);
};

#endif