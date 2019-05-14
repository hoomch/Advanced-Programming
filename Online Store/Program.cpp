#include "Program.hpp"

using namespace std;

void Program::add_user(string first_name, string last_name, string user_name, string phone, int money, 
					   string user_type, vector<string> sale)
{
	User* new_user = new User(first_name,last_name,user_name,phone,money,user_type,sale);
	if (check_user_name(user_name) == true) 
	{
		if(check_matching_user(first_name,last_name,user_name,phone,money,user_type) == true)
		{	
			cout << "‫‪Command‬‬ ‫‪OK‬‬" << endl;
			user_database.push_back(new_user);
		}
		else 
			cout << "‫‪Command‬‬ ‫‪Failed‬‬" << endl;
	}
	else 
	{
		user_database.push_back(new_user);
		cout << "‫‪Command‬‬ ‫‪OK‬‬" << endl;
	}

}

bool Program::check_user_name(string user_name)
{
	for(int i=0; i<user_database.size(); i++)
	{
		if (user_database[i]->get_id() == user_name)
				return true;
	}
	return false;
}

bool Program::check_matching_user(string first_name, string last_name, string user_name, 
								  string phone, int money, string user_type)
{
	for(int i=0; i<user_database.size(); i++)
	{
		if ((user_database[i]->get_id() == user_name)&&(user_database[i]->get_first_name() == first_name)&&
		   (user_database[i]->get_last_name() == last_name)&&(user_database[i]->get_phone() == phone)&&
		   (user_database[i]->get_type() != user_type)&&(user_database[i]->get_money() == money))
		{
			user_database[i]->change_type(user_type);
			return true;
		}
	}
	return false;
}

bool Program::add_goods(string seller_user_name, string goods_name, int goods_price, int goods_count)
{
	int which_user = find_user(seller_user_name);
	if (which_user == -1)
		return false;
	else if (user_database[which_user]->get_type() == "buyer")
		return false;
	else
	{
		Goods* new_goods = new Goods(seller_user_name,goods_name,goods_price,goods_count,0);
		if (goods_count >= 30)
			new_goods->decrease_price();
		goods_database.push_back(new_goods);
		check_requests();
		return true;
	}
}

void Program::check_requests()
{
	for (int i=0; i<req_database.size(); i++)
	{
		int count = 0;
		vector <Goods*> req_directory = req_database[i]->get_directory();
		for (int j=0; j<req_directory.size(); j++)
		{
			bool check_goods = check_avaiable_good(req_directory[j]);
			if (check_goods == true)
				count ++;
		}
		if (count == req_directory.size())
		{
			vector <vector <string>> buy_directory = convert_to_buy_list(req_directory);
			bool check = add_buy(buy_directory,req_database[i]->get_buyer());
			req_database.erase(req_database.begin() + i);
		}
	}
}

vector <vector <string>> Program::convert_to_buy_list(vector <Goods*> req_directory)
{
	vector <vector <string>> buy_directory;
	for (int i=0; i<req_directory.size(); i++)
	{
		vector <string> one_line;
		one_line.push_back(req_directory[i]->get_seller());
		one_line.push_back(to_string(req_directory[i]->get_count()));
		one_line.push_back(req_directory[i]->get_goods_name());
		buy_directory.push_back(one_line);
	}
	return buy_directory;
}

bool Program::check_avaiable_good(Goods* new_goods)
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if ((goods_database[i]->get_goods_name() == new_goods->get_goods_name())&&
			(goods_database[i]->get_seller() == new_goods->get_seller())&&
			(goods_database[i]->get_count() >= new_goods->get_count()))
			return true;
	}
	return false;
}

bool compare_goods(Goods* first, Goods* second)
{
	if(first->get_count() < second->get_count())
		return true;
	else if (first->get_count() > second->get_count())
		return false;
	if (first->get_price() < second->get_price())
		return true;
	else if (first->get_price() > second->get_price())
		return false;
	if (first->get_seller() < second->get_seller())
		return true;
	else
		return false;
}

void print_search_results(vector <Goods*> search_result)
{
	int count_number = 1;
	for (int i=0; i<search_result.size(); i++)
	{
		cout << count_number << ". " << search_result[i]->get_goods_name() << " " 
			 << search_result[i]->get_count() << " " << search_result[i]->get_price() 
			 << " " << search_result[i]->get_seller() << endl;
		count_number ++;
	}
}

void Program::search(string goods_name, string goods_count)
{
	
	vector <Goods*> search_result;
	for (int i=0; i<goods_database.size(); i++)
	{
		if ((goods_database[i]->get_goods_name() == goods_name)&&
			(goods_database[i]->get_count() >= stoi(goods_count)))
			search_result.push_back(goods_database[i]);
	}
	sort(search_result.begin(), search_result.end(), compare_goods);
	print_search_results(search_result);
	
}

void Program::search_sale()
{
	vector <Goods*> search_result;
	for (int i=0; i<goods_database.size(); i++)
		if (goods_database[i]->get_on_sale() == true)
			search_result.push_back(goods_database[i]);
	sort(search_result.begin(), search_result.end(), compare_goods);
	print_search_results(search_result);
}

void Program::search_special()
{
	vector <Goods*> search_result;
	for (int i=0; i<goods_database.size(); i++)
		if (goods_database[i]->get_is_special() == true)
			search_result.push_back(goods_database[i]);
	sort(search_result.begin(), search_result.end(), compare_goods);
	print_search_results(search_result);
}

bool Program::check_valid_buy(string goods_name, int goods_count, string seller)
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if ((goods_database[i]->get_goods_name() == goods_name)&&
		   (seller.find(goods_database[i]->get_seller()) != string::npos)&&
		   (goods_database[i]->get_count() >= goods_count))
				return true;
	}
	return false;
}

bool Program::check_existing_buy(string seller, string goods_name)
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if((goods_database[i]->get_goods_name() == goods_name)&&
		  (goods_database[i]->get_seller() == seller))
			return false;
	}
	return true;
}

bool Program::add_buy(vector<vector<string>> buy_directory, string buyer_name)
{
	bool valid = true;
	int total_sum = 0;
	int which_user = find_user(buyer_name);
	if (which_user == (-1))
		valid = false;
	for (int i=0; i<buy_directory.size(); i++)
	{
		vector <string> temp = buy_directory[i];
		if ((check_valid_buy(temp[0],stoi(temp[1]),temp[2]) == false)||
			(check_existing_buy(temp[2],temp[0]) == false))	
				valid = false;
		else 
			total_sum += (calculate_good_price(temp[0],temp[2],stoi(temp[1])));
	}
	if (user_database[which_user]->get_money() < (105/100*total_sum))
		valid = false;
	if (valid == false)
		return false;
	else
	{
		add_store_money(5/100*total_sum);
		add_seller_money(buy_directory);
		add_factor(buy_directory,buyer_name);
		update_goods(buy_directory);
		return true;
	}
}

void Program::add_seller_money(vector<vector<string>> buy_directory)
{
	for (int i=0; i<buy_directory.size(); i++)
	{
		int sum = 0;
		vector <string> temp = buy_directory[i];
		temp[2].pop_back();
		int which_user = find_user(temp[2]);
		sum += (calculate_good_price(temp[0],temp[2],stoi(temp[1])));
		user_database[which_user]->add_money(sum);
	}
}

int Program::find_user(string user_name)
{
	for(int i=0; i<user_database.size(); i++)
	{
		if (user_database[i]->get_id() == user_name)
			return i;
	}
	return (-1);
}

void Program::decrease_goods_count(string goods_name, int count, string seller)
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if ((goods_database[i]->get_goods_name() == goods_name)&&
			(seller.find(goods_database[i]->get_seller()) != string::npos))
		{	
			goods_database[i]->add_sold_number();
			goods_database[i]->decrease_quantity(count);
			if ((goods_database[i]->get_count() < 30)&&(goods_database[i]->get_on_sale() == true))
			{	
				goods_database[i]->change_sale_status();
				goods_database[i]->increase_price();
			}
		}
	}
}

int Program::calculate_good_price(string goods_name, string seller, int count)
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if ((goods_database[i]->get_goods_name() == goods_name)&&
	       (seller.find(goods_database[i]->get_seller()) != string::npos))
			return (goods_database[i]->get_price() * count);
	}
}

void Program::update_goods(vector<vector <string>> buy_directory)
{
	for (int i=0; i<buy_directory.size(); i++)
	{
		vector <string> temp = buy_directory[i];
		decrease_goods_count(temp[0],stoi(temp[1]),temp[2]);
	}
}

void Program::add_factor(vector<vector<string>> buy_directory, string buyer_name)
{
	int which_user = find_user(buyer_name);
	vector<vector<string> > factor_directory;
	for (int i=0; i<buy_directory.size(); i++)
	{
		vector <string> line;
		vector <string> temp = buy_directory[i];
		line.push_back(temp[0]);
		line.push_back(temp[1]);
		line.push_back(to_string(calculate_good_price(temp[0],temp[2],stoi(temp[1]))));
		line.push_back(temp[2]);
		line.push_back(to_string(stoi(line[1])*stoi(line[2])));
		factor_directory.push_back(line);
	}
	Factor* new_factor = new Factor(factor_number,0,user_database[which_user]->get_first_name(), 
									user_database[which_user]->get_last_name(), 
					  	 user_database[which_user]->get_id(),user_database[which_user]->get_phone(),factor_directory);
	print_one_factor(new_factor);
	factor_database.push_back(new_factor);
	user_database[which_user]->add_money(-new_factor->get_sum());
	factor_number ++;
}

void Program::print_one_factor(Factor* new_factor)
{
	cout << "Factor number " << new_factor->get_number() << endl;
	new_factor->print_all();
}

void Program::print_all_factors(string buyer_name)
{
	for (int i=0; i<factor_database.size(); i++)
	{
		if (factor_database[i]->get_id() == buyer_name)
		{
			cout << "Factor " << factor_database[i]->get_number() << " " << buyer_name << endl;
			factor_database[i]->print_all();
		}
	}
}

void Program::add_sale(string buyer_name, string goods_name, string seller)
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if ((goods_database[i]->get_goods_name() == goods_name)&&
			(goods_database[i]->get_seller() == seller))
		{
			int which_user = find_user(seller);
			vector <string> seller_discount_needers = user_database[which_user]->get_needers();
			int count = 0;
			for (int j=0; i<seller_discount_needers.size(); j++)
			{
				if (buyer_name == seller_discount_needers[j])
					count++;
			}
			if (count == 0)    
			{
				user_database[which_user]->add_needer(buyer_name);
				cout << "‫‪Command‬‬ ‫‪OK‬‬" << endl;
				if(seller_discount_needers.size() >= 9)
					goods_database[i]->decrease_price();
			}
			else 
				cout << "‫‪Command‬‬ ‫‪Failed‬‬" << endl;
		}
	}
}

void Program::show_trends()
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if (goods_database[i]->get_sold() >= 10)
			cout << goods_database[i]->get_goods_name() << endl;
	}
}

void Program::add_money(string user_name, int money)
{
	int which_user = find_user(user_name);
	user_database[which_user]->add_money(money);
	cout << "‫‪Command‬‬ ‫‪OK‬‬" << endl;
}

bool Program::add_request(vector<vector<string> > req_directory, string buyer_name,string req_name)
{
	vector <Goods*> requested_goods;
	for (int i=0; i<req_directory.size(); i++)
	{
		Goods* new_good = new Goods(req_directory[i][2],req_directory[i][0],0,stoi(req_directory[i][1]),0);
		requested_goods.push_back(new_good);
		if (req_name == req_database[i]->get_name())
			return false;
	}
	Request* new_req = new Request(req_name,buyer_name,requested_goods);
	req_database.push_back(new_req);
	return true;
}

void Program::print_req(string buyer_name)
{
	for (int i=0; i<req_database.size(); i++)
	{
		if (req_database[i]->get_buyer() == buyer_name)
		{
			req_database[i]->print();
		}
	}
}

bool Program::change_special(string seller, string goods_name, int goods_count, string choice)
{
	for (int i=0; i<goods_database.size(); i++)
	{
		if ((goods_database[i]->get_goods_name() == goods_name)&&
			(goods_database[i]->get_seller() == seller))
		{	
			if (goods_count > goods_database[i]->get_count())
				return false;
			else if (choice == "add")
			{
				goods_database[i]->set_special_count(goods_count);
				return true;
			}
			else if (choice == "remove")
			{
				goods_database[i]->set_special_count(-goods_count);
				return true;
			}
		}
	}
}

void Program::add_store_money(double amount)
{
	store_money += amount;
}