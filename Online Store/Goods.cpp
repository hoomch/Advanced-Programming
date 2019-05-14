#include "Goods.hpp"

using namespace std;

Goods::Goods(string _seller, string _name, int price, int count, int _sold)
{
	seller_name = _seller;
	goods_name = _name;
	goods_price = price;
	goods_count = count;
	sold = _sold;

}

void Goods::decrease_quantity(int amount)
{
	goods_count -= amount;
	sold += amount;
}

void Goods::decrease_price()
{
	if ((is_special == false)||(is_on_sale ==false))
		goods_price = goods_price * 9/10;
}

void Goods::increase_price()
{
	goods_price = goods_price * 11/10;
}

void Goods::change_sale_status()
{
	if (is_on_sale == true)
		is_on_sale = false;
	else 
		is_on_sale = true;
}

void Goods::change_special_status()
{
	if(is_special == true)
		is_special = false;
	else
		is_special = true;
}

void Goods::add_sold_number()
{
	sold++;
}

void Goods::set_special_count(int new_count)
{
	how_many_special += new_count;
}

