#include "Room.hpp"

using namespace std;

Room::Room(string name, string time, vector<string> joined, int count)
{
	room_name = name;
	current_time = time;
	joined_unroled_people = joined;
	time_count = count;
	votes_database = new Vote();
}

void Room::add_person(string person_name)
{
	joined_unroled_people.push_back(person_name);	
}

void Room::add_roles(map<string,int> count_directory)
{
	roles = count_directory;
}

int Room::calculate_map_size()
{
	int total_sum = 0;
	map<string,int>::iterator itr;
	for(itr = roles.begin(); itr != roles.end(); itr++)
	{
		total_sum += itr->second;
	}
	return total_sum;
}

int Room::size_of_database()
{
	return joined_unroled_people.size();
}

void Room::delete_database()
{
	joined_unroled_people.clear();
}

int randomfunc(int j) 
{ 
	srand(time(NULL));
    return rand() % j; 
}

void Room::randomise_vector()
{
	random_shuffle(people_inside.begin(), people_inside.end(), randomfunc);
} 

void Room::reset_votes()
{
	votes_database = NULL;
}

void Room::final_role_adding()
{
	map<string,int>::iterator itr;
	int count = 0;
	for(itr = roles.begin(); itr != roles.end(); itr++)
	{
		for(int i=0; i<(itr->second); i++)
		{
			if(itr->first == "RouinTan")
			{
				Bigman* new_person = new Bigman(joined_unroled_people[count],"RouinTan",0,0,2);
				people_inside.push_back(new_person);
				count++;
			}
			else if(itr->first == "Doctor")
			{
				Doctor* new_person = new Doctor(joined_unroled_people[count],"Doctor",0,0,1,0);
				people_inside.push_back(new_person);
				count++;
			}
			else if(itr->first == "Detective")
			{
				Detective* new_person = new Detective(joined_unroled_people[count],"Detective",0,0,1,0);
				people_inside.push_back(new_person);
				count++;
			}
			else if(itr->first == "Villager")
			{
				Person* new_person = new Person(joined_unroled_people[count],"Villager",0,0,1);
				people_inside.push_back(new_person);
				count++;
			}
			else if(itr->first == "GodFather")
			{
				Person* new_person = new Person(joined_unroled_people[count],"GodFather",0,0,1);
				people_inside.push_back(new_person);
				count++;
			}
			else if(itr->first == "Silencer")
			{
				Silencer* new_person = new Silencer(joined_unroled_people[count],"Silencer",0,0,1,0);
				people_inside.push_back(new_person);
				count++;
			}
			else if(itr->first == "Mafia")
			{
				Person* new_person = new Person(joined_unroled_people[count],"Mafia",0,0,1);
				people_inside.push_back(new_person);
				count++;
			}
			else if(itr->first == "Joker")
			{
				Joker* new_person = new Joker(joined_unroled_people[count],"Joker",0,0,1);
				people_inside.push_back(new_person);
				count++;
			}
		}
	}
}

void Room::print_roles()
{
	for (int i=0; i<people_inside.size(); i++)
	{
		cout << people_inside[i]->get_name() << " is " << people_inside[i]->get_role() << endl;
	}
}

Person* Room::check_person(string person_name)
{
	for (int i = 0; i<people_inside.size(); i++)
	{
		if (people_inside[i]->get_name() == person_name)
		{
			return people_inside[i];
		}
	}
	return NULL;
}

bool Room::check_if_sileced(string person_name)
{
	Person* new_person = check_person(person_name);
	if (new_person == NULL)
		return false;
	if (new_person->get_silence_status() == true)
		return true;
	else
		return false;
}

bool Room::check_if_dead(string person_name)
{
	Person* new_person = check_person(person_name); 
	if (new_person == NULL)
		return false;
	if (new_person->get_health_status() == 0)
		return true;
	else
		return false;
}

bool Room::check_already_voted(string person_name)
{
	if(votes_database->check_double_vote(person_name) == true)
		return true;
	else
		return false;
}

void Room::add_vote(string voter, string votee)
{
	votes_database->add_vote(voter,votee);
}

Person* Room::calculate_votes()
{
	string person_name = votes_database->kill();
	Person* victim = check_person(person_name);
	victim->kill_person();
	return victim;
}

bool Room::check_if_all_voted()
{
	return (this->mafia_count() == votes_database->get_size());
}

bool Room::check_already_asked(Person* under_inspection)
{
	if (under_inspection->get_power_status() == true)
		return true;
	else 
		return false;
}

string Room::ask(Person* new_detective, Person* suspect)
{
	string result;
	if ((suspect->get_role() == "Mafia") || (suspect->get_role() == "Silencer"))
		result = "Yes";
	else 
		result = "No";
	new_detective->action();
	return result;
}

bool Room::check_already_healed(Person* under_inspection)
{
	if(under_inspection->get_power_status() == true)
		return true;
	else
		return false;
}

void Room::heal(Person* new_doctor, Person* patient)
{
	patient->add_protection();	
	new_doctor->action();
}

bool Room::check_already_silenced(Person* under_inspection)
{
	if(under_inspection->get_power_status() == true)
		return true;
	else 
		return false;
}

void Room::silence(Person* new_silencer, Person* victim)
{
	victim->make_silent();
	new_silencer->action();
}

int Room::mafia_count()
{
	int alive_count = 0;
	for(int i=0; i<people_inside.size(); i++)
	{
		if ((people_inside[i]->get_health_status() != 0)&&((people_inside[i]->get_role() == "Mafia")||
			(people_inside[i]->get_role() == "Silencer")||(people_inside[i]->get_role() == "GodFather")))
		alive_count ++;
	}
	return alive_count;
}

int Room::villager_count()
{
	int alive_count = 0;
	for(int i=0; i<people_inside.size(); i++)
	{
		if ((people_inside[i]->get_health_status() != 0)&&((people_inside[i]->get_role() == "Villager")||
			(people_inside[i]->get_role() == "Doctor")||(people_inside[i]->get_role() == "RouinTan")||
			(people_inside[i]->get_role() == "Detective")))
		alive_count ++;
	}
	return alive_count;
}

void Room::show_time()
{
	cout << current_time << " " << time_count << endl;
}

void Room::change_time_to(string what_time)
{
	if (what_time == "Night")
		current_time = "Night";
	else 
	{
		current_time = "Day";
		time_count ++;
	}
}

void Room::specials_counted_plus()
{
	specials_acted ++;
}

bool Room::check_all_acted()
{
	int count = 0;
	for(int i=0; i<people_inside.size(); i++)
	{
		if ((people_inside[i]->get_health_status() != 0)&&((people_inside[i]->get_role() == "Doctor")||
			(people_inside[i]->get_role() == "Silencer")||(people_inside[i]->get_role() == "Detective")))
		count ++;
	}
	if (count == specials_acted)
		return true;
	else
		return false;
}

void Room::show_silenced()
{
	for(int i=0; i<people_inside.size(); i++)
	{
		if(people_inside[i]->get_silence_status() == true)
			cout << "Silenced " << people_inside[i]->get_name() << endl;
	}
}

void Room::reset_acts()
{
	for(int i=0; i<people_inside.size(); i++)
	{
		people_inside[i]->reset();
	}
}



