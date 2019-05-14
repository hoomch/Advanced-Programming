#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>

#include <string>

#include <vector>

#include <algorithm>

#include "User.hpp"

#include "Goods.hpp"

#include "Factor.hpp"

#include "Request.hpp"

class Program
{
	private:
		int factor_number = 1;
		int store_money = 0;
		std::vector<User*> user_database;
		std::vector<Goods*> goods_database;
		std::vector<Factor*> factor_database;
		std::vector<Request*> req_database;

	public:
	    Program() = default;
		void add_user(std::string first_name, std::string last_name, std::string user_name,
		              std::string phone, int money, std::string user_type, std::vector<std::string> sale);
		bool check_user_name(std::string user_name);
		bool check_matching_user(std::string first_name, std::string last_name, std::string user_name,
		              std::string phone, int money, std::string user_type);
		void add_money(std::string user_name, int money);
		int find_user(std::string user_name);
		void decrease_goods_count(std::string goods_name, int count, std::string seller);
		bool add_goods(std::string seller_user_name, std::string goods_name, int goods_price,
					   int goods_count);
		void search(std::string goods_name, std::string goods_count);
		bool check_valid_buy(std::string goods_name, int goods_count, std::string seller);
		bool check_existing_buy(std::string seller, std::string goods_name);
		bool add_buy(std::vector<std::vector<std::string> > buy_directory, std::string buyer_name);
		void add_seller_money(std::vector<std::vector<std::string> > buy_directory);
		int calculate_good_price(std::string goods_name, std::string seller, int count);
		void update_goods(std::vector<std::vector<std::string> > buy_directory);
		void add_factor(std::vector<std::vector<std::string> > buy_directory, std::string buyer_name);
		void print_one_factor(Factor* new_factor);
		void print_all_factors(std::string buyer_name);
		void add_sale(std::string buyer_name, std::string goods_name, std::string seller);
		void show_trends();
		bool add_request(std::vector<std::vector<std::string> > req_directory, std::string buyer_name,
						 std::string req_name);
		void print_req(std::string buyer_name);
		bool change_special(std::string seller, std::string goods_name, int goods_count, std::string choice);
		void add_store_money(double amount);
		void check_requests();
		bool check_avaiable_good(Goods* new_goods);
		void search_sale();
		void search_special();
		std::vector<std::vector<std::string> > convert_to_buy_list(std::vector <Goods*> req_directory);
};

#endif