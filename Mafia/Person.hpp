#ifndef PERSON_H
#define PERSON_H

#include <iostream>

#include <vector>

#include <string>

class Person
{
	public:
		Person(std::string _name,std::string _role, bool _silenced, bool _extra, int _health);
		void add_role(std::string role_name);
		void add_protection();
		void make_silent();
		std::string get_name() {return name;}
		std::string get_role() {return role;}
		int get_health_status() {return health;}
		bool get_silence_status() {return is_silenced;}
		bool get_protection_status() {return is_healed;}
		void kill_person();
		void reset();
		virtual void action();
		virtual bool get_power_status() {return true;}

	protected:
		std::string name,role;
		bool is_silenced,is_healed;
		int health;
};


#endif