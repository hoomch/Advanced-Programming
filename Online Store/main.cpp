#include <iostream>

#include <string> 

#include <sstream> 

#include <vector>

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
	bool check;
	vector<string> parsed,buy_parsed;
	vector<string> sale;
	while(getline(cin,to_read)){
		parsed = parse_line(to_read);
		if(parsed[0] == "add_user")
		{
			int money = stoi(parsed[5]);
			program.add_user(parsed[1],parsed[2],parsed[3],parsed[4],money,parsed[6],sale);
		}
		else if (parsed[0] == "add_goods")
		{
			check = program.add_goods(parsed[1], parsed[2], stoi(parsed[3]),stoi(parsed[4]));
			if (check == true)
				cout << "‫‪Command‬‬ ‫‪OK‬‬" << endl;
			else 
				cout << "‫‪Command‬‬ ‫‪Failed‬‬" << endl;
		}
		else if (parsed[0] == "search")
		{
			program.search(parsed[1],parsed[2]);
		}
		else if (parsed[0] == "buy")
		{
			char c;
			vector<vector <string>> buy_directory;
			string buyer_name = parsed[1];
			to_read.erase(to_read.end() - 1);
			parsed = parse_line(to_read);
			parsed.erase(parsed.begin() + 0);
			parsed.erase(parsed.begin() + 0);
			buy_directory.push_back(parsed);
			vector<string> buy_list;
			do
			{
				getline (cin,to_read);
				if (!to_read.size())
					break;
			    c = to_read[to_read.size() - 1];
				to_read.erase(to_read.end() - 1);
				buy_list = parse_line(to_read);
				buy_directory.push_back(buy_list);
			} while (c != ';');
			check = program.add_buy(buy_directory, buyer_name);
			if (check == false)
				cout << "‫‪Command‬‬ ‫‪Failed" << endl;	
		}
		else if (parsed[0] == "add_special")
		{
			check = program.change_special(parsed[1],parsed[2],stoi(parsed[3]),"add");
			if (check == false)
				cout << "‫‪Command‬‬ ‫‪Failed" << endl;
			else 
				cout << "‫‪Command‬‬ ‫‪OK‬‬" << endl;
		}
		else if (parsed[0] == "remove_special")
		{
			check = program.change_special(parsed[1],parsed[2],stoi(parsed[3]),"remove");
			if (check == false)
				cout << "‫‪Command‬‬ ‫‪Failed" << endl;
			else 
				cout << "‫‪Command‬‬ ‫‪OK‬‬" << endl;
		}
		else if (parsed[0] == "print_factor")
		{
			program.print_all_factors(parsed[1]);
		}
		else if (parsed[0] == "sale")
		{
			program.add_sale(parsed[1],parsed[2],parsed[3]);
		}
		else if (parsed[0] == "‫‪search_sale")
		{
			program.search_sale();
		}
		else if (parsed[0] == "‫‪search_bestseller")
		{
			program.search_special();
		}
		else if (parsed[0] == "‫‪add_money‬‬")
		{
			program.add_money(parsed[1],stoi(parsed[2]));
		}
		else if (parsed[0] == "‫‪request")
		{
			char c;
			vector<vector<string> > req_directory;
			string req_name = parsed[1];
			string buyer_name = parsed[2];
			to_read.erase(to_read.end() - 1);
			parsed = parse_line(to_read);
			parsed.erase(parsed.begin() + 0);
			parsed.erase(parsed.begin() + 0);
			parsed.erase(parsed.begin() + 0);
			req_directory.push_back(parsed);
			vector<string> req_list;
			do
			{
				getline (cin,to_read);
				if (!to_read.size())
					break;
			    c = to_read[to_read.size() - 1];
				to_read.erase(to_read.end() - 1);
				req_list = parse_line(to_read);
				req_directory.push_back(req_list);
			} while (c != ';');
			check = program.add_request(req_directory,buyer_name,req_name);
			if (check == false)
				cout << "‫‪Command‬‬ ‫‪Failed" << endl;
		}
		else if (parsed[0] == "‫‪print_request")
		{
			program.print_req(parsed[1]);
		}
		else 
		{
			cout << "‫‪Command‬‬ ‫‪Failed‬‬" << endl;
		}
	}
}
