#ifndef GOODS_H
#define GOODS_H

#include <iostream>

class Goods
{
	private:
		std::string seller_name,goods_name;
		int goods_price,goods_count,sold;
		bool is_on_sale,is_special = false;
		int how_many_special = 0;

	public:
		Goods(std::string _seller, std::string _name, int price, int count, int _sold);
		std::string get_goods_name() {return goods_name;}
		std::string get_seller() {return seller_name;}
		int get_price() {return goods_price;}
		int get_count() {return goods_count;}
		void change_special_status();
		void set_special_count(int new_count);
		int get_sold() {return sold;}
		void add_sold_number();
		bool get_on_sale() {return is_on_sale;}
		bool get_is_special() {return is_special;}
		void change_sale_status();
		void decrease_quantity(int amount);
		void decrease_price();
		void increase_price();
};

#endif