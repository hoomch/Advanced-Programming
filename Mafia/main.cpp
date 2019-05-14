#include <iostream>

#include <vector>

#include <string>

#include "Program.hpp"

using namespace std;

vector<string> parse_line(string input)
{
	string temp_parsing = "";
	vector<string> parsed;
	for (int i=0; i<=input.size(); i++)
	{
		if((input[i] == ' ')&&(temp_parsing.size() >= 1))
		{
			parsed.push_back(temp_parsing);
			temp_parsing = "";
		}
		else
			temp_parsing.push_back(input[i]);
	}
	if(temp_parsing.size() >= 1)
		parsed.push_back(temp_parsing);
	return parsed;
}

int main()
{
	Program program;
	string to_read;
	vector<string> parsed;
	while(getline(cin,to_read))
	{
		parsed = parse_line(to_read);
		if(parsed[0] == "Create_room")
		{
			try
			{	
				if (parsed.size() <= 2)
					throw Not_enough_data();
				program.create_room(parsed);
			}
			catch(Not_enough_data ex)
			{
				cout << "Please check your inputs!" << endl;
			}
			catch(room_name_exists ex)
			{
				cout << "This room has already been created!" << endl;
			}
			catch(Role_type_ex ex)
			{
				cout << "Check your roles!" << endl;
			}
			catch(Wrong_role_combination ex)
			{
				cout << "Special roles more than normal!" << endl;
			}

		}
		else if(parsed[0] == "Switch_room")
		{
			try
			{
				if (parsed.size() <= 1)
					throw Invalid_room_name();
				string room_name = parsed[1];
				program.switch_room(room_name);
			}
			catch(Invalid_room_name ex)
			{
				cout << "Invalid_room_name" << endl;
			}
		}
		else if(parsed[0] == "Join")
		{
			try
			{
				program.join_player(parsed);
			}
			catch(Many_users ex)
			{
				cout << "many users" << endl;
			}
		}
		else if(parsed[0] == "Get_room_state")
		{
			program.show_state();
		}
		else if(parsed[0] == "Vote")
		{
			try
			{
				if (parsed.size() <= 2)
					throw Not_enough_data();
				program.decide_which_vote_type(parsed);
			}
			catch(Not_enough_data ex)
			{
				cout << "Please check your inputs!" << endl;
			}
			catch(User_not_joined ex)
			{
				cout << "User not joined" << endl;
			}
			catch(User_dead ex)
			{
				cout << "‫‪User‬‬ ‫‪already‬‬ ‫‪died‬‬" << endl;
			}
			catch(User_silenced ex)
			{
				cout << "‫‪This‬‬ ‫‪user‬‬ ‫‪has‬‬ ‫‪been‬‬ ‫‪silenced‬‬ ‫‪before‬‬" << endl;
			}
			catch(User_already_voted ex)
			{
				cout << "User already voted!" << endl;
			}
			catch(Invalid_power_use ex)
			{
				cout << "This user can not vote" << endl;
			}
		}
		else if(parsed[0] == "End_vote")
		{
			program.end_day_vote();
		}
		else if(parsed[0] == "Detect")
		{
			try
			{
				if (parsed.size() <= 3)
					throw Not_enough_data();
				program.detect(parsed);
			}
			catch(Not_enough_data ex)
			{
				cout << "Please check your inputs!" << endl;
			}
			catch(Already_used_power ex)
			{
				cout << "‫‪Detective‬‬ ‫‪has‬‬ ‫‪alreay‬‬ ‫‪asked‬‬" << endl;
			}
			catch(Invalid_power_use ex)
			{
				cout << "User can not ask" << endl;
			}
			catch(User_dead ex)
			{
				cout << "Person is dead" << endl;
			}
			catch(User_not_joined ex)
			{
				cout << "User not joined" << endl;
			}
		}
		else if(parsed[0] == "Heal")
		{
			try
			{
				if (parsed.size() <= 3)
					throw Not_enough_data();
				program.heal(parsed);
			}
			catch(Not_enough_data ex)
			{
				cout << "Please check your inputs!" << endl;
			}
			catch(Already_used_power ex)
			{
				cout << "‫‪‫‪Doctor‬‬ ‫‪has‬‬ ‫‪alreay‬‬ ‫‪healed‬‬" << endl;
			}
			catch(Invalid_power_use ex)
			{
				cout << "User can not heal" << endl;
			}
			catch(User_dead ex)
			{
				cout << "Person is dead" << endl;
			}
			catch(User_not_joined ex)
			{
				cout << "User not joined" << endl;
			}
		}
		else if(parsed[0] == "Silent")
		{
			try
			{
				if (parsed.size() <= 3)
					throw Not_enough_data();
				program.silent(parsed);
			}
			catch(Not_enough_data ex)
			{
				cout << "Please check your inputs!" << endl;
			}
			catch(Already_used_power ex)
			{
				cout << "‫‪‫‪Silencer ‫‪has‬‬ ‫‪alreay‬‬ ‫‪‫‪silenced‬‬" << endl;
			}
			catch(Invalid_power_use ex)
			{
				cout << "User can not silence" << endl;
			}
			catch(User_dead ex)
			{
				cout << "Person is dead" << endl;
			}
			catch(User_not_joined ex)
			{
				cout << "User not joined" << endl;
			}
		}
		else 
		{
			cout << "Wrong command!" << endl;
		}
	}
}