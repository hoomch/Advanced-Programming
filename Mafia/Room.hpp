#ifndef ROOM_H
#define ROOM_H

#include <iostream>

#include <vector>

#include <string>

#include <map>

#include <algorithm>

#include "Person.hpp"
#include "Doctor.hpp"
#include "Bigman.hpp"
#include "Joker.hpp"
#include "Silencer.hpp"
#include "Detective.hpp"
#include "Vote.hpp"

class Room
{
	public:
		Room(std::string name, std::string time, std::vector<std::string> joined, int count);
		void add_person (std::string person_name);
		void change_time();
		std::string get_name() {return room_name;}
		std::string get_time() {return current_time;}
		int get_time_count() {return time_count;}
		void add_roles (std::map<std::string,int> count_directory);
		int calculate_map_size();
		int size_of_database();
		void delete_database();
		void randomise_vector();
		void final_role_adding();
		void print_roles();
		Person* check_person(std::string person_name);
		bool check_if_sileced(std::string person_name);
		bool check_if_dead(std::string person_name);
		bool check_already_voted(std::string person_name);
		void add_vote(std::string voter, std::string votee);
		Person* calculate_votes();
		bool check_if_all_voted();
		int mafia_count();
		int villager_count();
		void show_time();
		void reset_votes();
		void change_time_to(std::string what_time);
		bool check_already_asked(Person* under_inspection);
		bool check_already_healed(Person* under_inspection);
		bool check_already_silenced(Person* under_inspection);
		std::string ask(Person* new_detective, Person* suspect);
		void heal(Person* new_doctor, Person* patient);
		void silence(Person* new_silencer, Person* victim);
		void specials_counted_plus();
		bool check_all_acted();
		void show_silenced();
		void reset_acts();

	private:
		std::string room_name;
		std::vector <Person*> people_inside;
		std::map <std::string,int> roles;
		std::string current_time;
		std::vector<std::string> joined_unroled_people;
		Vote* votes_database;
		int time_count;
		int specials_acted = 0;


};

#endif