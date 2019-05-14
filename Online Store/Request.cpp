#include "Request.hpp"

using namespace std;

Request::Request(std::string _name, std::string _buyer,std::vector<Goods*> _directory)
{
	req_name = _name;
	buyer_name = _buyer;
	directory = _directory;
}

void Request::print()
{
	int count = 1;
	cout << "Request " << count << " " << req_name << " " << buyer_name << endl;
	for (int i=0; i<directory.size(); i++)
	{
		cout << i+1 << ". " << directory[i]->get_goods_name() << " " << directory[i]->get_count() << " "
		<< directory[i]->get_seller() << endl;
	}
}