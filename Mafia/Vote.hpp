#ifndef VOTE_H
#define VOTE_H

#include <iostream>

#include <vector>

#include <string>

#include <map>

class Vote
{
	public:
		Vote(){};
		void add_vote(std::string voter_name, std::string votee_name);
		bool check_double_vote(std::string voter_name);
		int get_size() {return vote_database.size();}
		std::string kill();
	private:
		std::map <std::string,std::string> vote_database;
	
};

#endif