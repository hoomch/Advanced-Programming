#include "Program.hpp"

using namespace std;

void Program::create_room(vector <string> new_room_info)
{
	if (check_room_name(new_room_info[1]) != NULL)
		throw room_name_exists();
	else 
	{
		vector <string> allowed_roles {"Mafia","Villager","Doctor","Detective","RouinTan","Silencer","GodFather"};
		map<string,int> count_directory = make_role_chart(new_room_info,allowed_roles);
		if (!check_role_combination(count_directory))
			throw Wrong_role_combination();
		int villager_specials = count_villager_specials(count_directory);
		int mafia_specials = count_mafia_specials(count_directory);
		count_directory["Mafia"] = count_directory["Mafia"] - mafia_specials;
		count_directory["Villager"] = count_directory["Villager"] - villager_specials;
		add_room(count_directory,new_room_info[1]);
	}
}

int Program::count_villager_specials(map<string,int> count_directory)
{
	int villager_specials = count_directory["Doctor"] + count_directory["Detective"] + count_directory["RouinTan"];
	return villager_specials;
}

int Program::count_mafia_specials(map<string,int> count_directory)
{
	int mafia_specials = count_directory["GodFather"] + count_directory["Silencer"];
	return mafia_specials;
}

Room* Program::check_room_name(string room_name)
{
	for (int i=0; i<database.size(); i++)
	{
		if (database[i]->get_name() == room_name)
			return database[i]; 
	}
	return NULL;
}

map<string,int> Program::make_role_chart(vector<string> new_room_info,vector<string> allowed_roles)
{
	map<string,int> count_directory;
	for (int i=0; i<7; i++)
		count_directory[allowed_roles[i]] = 0;
	for (int i=2; i<new_room_info.size(); i+=2)
	{
		if (new_room_info[i] == "-Mafia")
			count_directory["Mafia"] = stoi(new_room_info[i+1]);
		else if (new_room_info[i] == "-Villager")
			count_directory["Villager"] = stoi(new_room_info[i+1]);
		else if (new_room_info[i] == "-Doctor")
			count_directory["Doctor"] = stoi(new_room_info[i+1]);
		else if (new_room_info[i] == "-GodFather")
			count_directory["GodFather"] = stoi(new_room_info[i+1]);
		else if (new_room_info[i] == "-Silencer")
			count_directory["Silencer"] = stoi(new_room_info[i+1]);
		else if (new_room_info[i] == "-RouinTan")
			count_directory["RouinTan"] = stoi(new_room_info[i+1]);
		else if (new_room_info[i] == "-Detective")
			count_directory["Detective"] = stoi(new_room_info[i+1]);
		else
			throw Role_type_ex();
	}
	return count_directory;
}

bool Program::check_role_combination(map<string,int> count_directory)
{
	int villager_specials = count_villager_specials(count_directory);
	int mafia_specials = count_mafia_specials(count_directory);
	if (count_directory["Villager"] < villager_specials) 
		return false;
	if (count_directory["Mafia"] < mafia_specials)
		return false;
	return true;
}

void Program::add_room(map<string,int> count_directory,string room_name)
{
	vector <string> empty_vector;
	Room* new_room = new Room(room_name, "Day", empty_vector,1);
	new_room->add_roles(count_directory);
	database.push_back(new_room);
	current_room = new_room;
	check_wins();
}

void Program::switch_room(string room_name)
{
	int length = room_name.size();
	room_name.erase(room_name.begin() + (length - 1));
	if (check_room_name(room_name) == NULL)
		throw Invalid_room_name();
	else
	{
		Room* next_room = check_room_name(room_name);
		set_current_room(next_room);
	}
}

void Program::set_current_room(Room* next_room)
{
	current_room = next_room;
}

void Program::join_player(vector <string> players)
{
	int allowed_size = current_room->calculate_map_size();
	for (int i=1; i<players.size(); i++)
	{
		current_room->add_person(players[i]);
	}
	if(current_room->size_of_database() > allowed_size)
	{
		current_room->delete_database();
		throw Many_users();
	}
	else if(current_room->size_of_database() == allowed_size)
	{
		cast_roles_to_players(current_room);
	}

}

void Program::cast_roles_to_players(Room* current_room)
{
	current_room->randomise_vector();
	current_room->final_role_adding();
	current_room->print_roles();
	current_room->show_time();
	for (int i=0; i<database.size(); i++)
	{
		if (current_room->get_name() == database[i]->get_name())
			database[i] = current_room;
	}
}

void Program::decide_which_vote_type(vector<string> new_votes)
{
	string time_now = current_room->get_time(); 
	if (time_now.find("Day") != string::npos)
		day_vote(new_votes);
	else
		night_vote(new_votes);
}

void Program::day_vote(vector<string> new_votes)
{
	check_wins();
	string voter_name = new_votes[1];
	string votee_name = new_votes[2];
	votee_name.pop_back();
	if((current_room->check_person(voter_name) == NULL)||(current_room->check_person(votee_name) == NULL))
		throw User_not_joined();
	if(current_room->check_if_sileced(voter_name) == true)
		throw User_silenced();
	if(current_room->check_if_dead(votee_name) == true)
		throw User_dead();
	if(current_room->check_already_voted(voter_name) == true)
		throw User_already_voted();
	else
		current_room->add_vote(voter_name,votee_name);
}

void Program::end_day_vote()
{
	Person* just_died = current_room->calculate_votes();
	cout << "Died " << just_died->get_name() << endl;
	current_room->change_time_to("Night");
	current_room->show_time();
	current_room->reset_votes();
}

void Program::night_vote(vector<string> new_votes)
{
	string voter_name = new_votes[1];
	string votee_name = new_votes[2];
	votee_name.pop_back();
	Person* vote_person = current_room->check_person(voter_name);
	Person* votee_person = current_room->check_person(votee_name);
	if((votee_person == NULL)||(votee_person == NULL))
		throw User_not_joined();
	if(current_room->check_if_dead(votee_name) == true)
		throw User_dead();
	if(current_room->check_already_voted(voter_name) == true)
		throw User_already_voted();
	if((vote_person->get_role() != "Mafia")&&(vote_person->get_role() != "Silencer")&&
		(vote_person->get_role() != "GodFather"))
		throw Invalid_power_use();
	else
	{
		current_room->add_vote(voter_name,votee_name);
		bool check = current_room->check_if_all_voted();
		if (check == true) 
			end_night_vote();
	}
}

void Program::end_night_vote()
{
	Person* just_died = current_room->calculate_votes();
	cout << "Mafia try to kill " << just_died->get_name() << endl;
}

void Program::detect(vector <string> detection)
{
	Person* detective = current_room->check_person(detection[1]);
	Person* suspect = current_room->check_person(detection[2]);
	if (detective->get_role() != "Detective")
		throw Invalid_power_use();
	else if ((detective == NULL) || (suspect == NULL))
		throw User_not_joined();
	else if(current_room->check_already_asked(detective) == true)
		throw Already_used_power();
	else if(current_room->check_if_dead(detective->get_name()) == true)
		throw Invalid_power_use();
	else if(current_room->check_if_dead(suspect->get_name()) == true)
		throw User_dead();
	else
	{
		string answer = current_room->ask(detective,suspect);
		cout << answer << endl;
		current_room->specials_counted_plus();
	}
}

void Program::heal(vector <string> heal_list)
{
	Person* doctor = current_room->check_person(heal_list[1]);
	Person* patient = current_room->check_person(heal_list[2]);
	if (doctor->get_role() != "Doctor")
		throw Invalid_power_use();
	else if ((doctor == NULL) || (patient == NULL))
		throw User_not_joined();
	else if(current_room->check_already_healed(doctor) == true)
		throw Already_used_power();
	else if(current_room->check_if_dead(doctor->get_name()) == true)
		throw Invalid_power_use();
	else if(current_room->check_if_dead(patient->get_name()) == true)
		throw User_dead();
	else
	{
		current_room->heal(doctor,patient);
		current_room->specials_counted_plus();
	}
}

void Program::silent(vector <string> silence_list)
{
	Person* silencer = current_room->check_person(silence_list[1]);
	Person* victim = current_room->check_person(silence_list[2]);
	if (silencer->get_role() != "Silencer")
		throw Invalid_power_use();
	else if ((silencer == NULL) || (victim == NULL))
		throw User_not_joined();
	else if(current_room->check_already_silenced(silencer) == true)
		throw Already_used_power();
	else if(current_room->check_if_dead(silencer->get_name()) == true)
		throw Invalid_power_use();
	else if(current_room->check_if_dead(victim->get_name()) == true)
		throw User_dead();
	else
	{
		current_room->silence(silencer,victim);
		current_room->specials_counted_plus();
	}
	if(current_room->check_all_acted() == true)
		finalise_night();
}

void Program::finalise_night()
{
	Person* just_died = current_room->calculate_votes();
	current_room->reset_votes();
	if(just_died->get_role() == "Joker")
		cout << "Joker win!" << endl;
	current_room->change_time_to("Day");
	current_room->show_time();
	if(just_died->get_protection_status() == false)
	{
		just_died->kill_person();
		if(just_died->get_health_status() == 0)
			cout << "Killed " << just_died->get_name() << endl;
	}
	current_room->show_silenced();
	current_room->reset_acts();
}


void Program::show_state()
{
	int alive_villagers = current_room->villager_count();
	int alive_mafia = current_room->mafia_count();
	cout << "Mafia = " << alive_mafia << endl;
	cout << "Villager = " << alive_villagers << endl;
}

void Program::check_wins()
{
	bool check = false;
	if (current_room->mafia_count() > current_room->villager_count())
		check = true;
	if (check == true)
		cout << "Loose!" << endl;
	else if (current_room->mafia_count() == 0)
		cout << "Victory!" << endl;
}

