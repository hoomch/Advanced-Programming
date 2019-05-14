#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

#include <vector>

#include <string>

#include <map>

#include <algorithm>

#include <cstdlib>

#include "Room.hpp"
#include "Person.hpp"
#include "Doctor.hpp"
#include "Bigman.hpp"
#include "Joker.hpp"
#include "Silencer.hpp"
#include "Detective.hpp"

class Not_enough_data {};
class room_name_exists {};
class Invalid_room_name {};
class Wrong_role_combination {};
class Role_type_ex {};
class Many_users {};
class User_not_joined {};
class User_silenced {};
class User_dead {};
class User_already_voted {};
class Already_used_power {};
class Invalid_power_use {};


class Program
{
	public:
		Program() = default;
		void create_room(std::vector <std::string> new_room);
		Room* check_room_name(std::string room_name);
		std::map<std::string,int> make_role_chart(std::vector <std::string> new_room_info,
			std::vector<std::string> allowed_roles);
		bool check_role_combination(std::map<std::string,int> count_directory);
		void add_room(std::map<std::string,int> count_directory,std::string room_name);
		int count_villager_specials(std::map<std::string,int> count_directory);
		int count_mafia_specials(std::map<std::string,int> count_directory);
		void switch_room(std::string room_name);
		void set_current_room(Room* next_room);
		void join_player(std::vector <std::string> players);
		void cast_roles_to_players(Room* current_room);
		void day_vote(std::vector <std::string> new_votes);
		void night_vote(std::vector <std::string> new_votes);
		void decide_which_vote_type(std::vector <std::string> new_votes);
		void end_day_vote();
		void end_night_vote();
		void detect(std::vector <std::string> detection);
		void heal(std::vector <std::string> heal_list);
		void silent(std::vector <std::string> silence_list);
		void show_state();
		void check_wins();
		void finalise_night();


	private:
		std::vector <Room*> database;
		Room* current_room;


	
};

#endif