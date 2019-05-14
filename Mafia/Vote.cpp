#include "Vote.hpp"

using namespace std;

void Vote::add_vote(string voter_name, string votee_name)
{
	vote_database[voter_name] = votee_name;
}

bool Vote::check_double_vote(string voter_name)
{
	map<string,string>::iterator itr;
	for(itr = vote_database.begin(); itr != vote_database.end(); itr++)
	{
		if(itr->first == voter_name)
			return true;
	}
	return false;
}

string Vote::kill()  
{
	map<string,string>::iterator itr;
	map<string,int> each_person_votes;
	map<string,int>::iterator sec_itr;
	string killed_name;
	int max_voted = 1;
	for(itr = vote_database.begin(); itr != vote_database.end(); itr++)
	{
		each_person_votes[itr->second] ++; 
	}
	for(sec_itr = each_person_votes.begin(); sec_itr != each_person_votes.end(); sec_itr++)
	{
		if((sec_itr->second) > max_voted)
		{
			killed_name = sec_itr->first;
			max_voted = sec_itr->second;
		}
	}
	return killed_name;
}