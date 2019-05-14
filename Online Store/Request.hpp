#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

#include <vector>

#include "Goods.hpp"

class Request
{
	private:
		std::string req_name,buyer_name;
		std::vector<Goods*> directory;

	public:
		Request(std::string _name, std::string _buyer,std::vector<Goods*> _directory);
		void print();
		std::string get_buyer() {return buyer_name;}
		std::string get_name() {return req_name;}
		std::vector<Goods*> get_directory() {return directory;}
};

#endif