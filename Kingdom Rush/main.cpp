#include <iostream>
#include "rsdl.hpp"
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <fstream>
#include <utility>
#include <chrono>
#include <string>
using namespace std;
using namespace chrono;

#define map1_details "assets/levels/1/map1_details.txt"
#define map2_details "assets/levels/2/map2_details.txt"
#define png_address "assets/png_address.txt"
#define standard_font "assets/FreeSans.ttf" 
//---------------------------------------------------------
enum Unit_Form{
	orc,
	armored,
	wolf,
	demon
};
//----------------------------------------------------------
enum Tower_Kind{
	archer,
	canon,
	mage,
	icy
};
//----------------------------------------------------------
enum Direction{
	Up,
	Down,
	Right,
	Left
};
//---------------------------------------------------------
struct Turning_Point{
	pair<int,int> cord;
	Direction direct;
};
//--------------------------------------------------------
struct Unit_live{
	Unit_Form form;
	pair<int,int> cord;
	int prime_distance;
	int health;
	int speed;
	int gold_recive;
	int fight_power;
	int size;
	Direction face;
	bool dead;
	double life_time;
	double start_living_time;
	bool freazing;
	double start_freazing_time;
};
//-------------------------------------------------------------
struct Tower_Build{
	Tower_Kind kind;
	pair<int,int> little_cord;
	pair<int,int> large_cord;
	int price;
	int damage;
	int size;
	double attack_speed;
	double last_time_shut;
	bool exist;
};
//--------------------------------------------------------------
struct Tower_Attack{
	Tower_Kind type;
	pair<int,int> cord;
	int damage;
	double speed;
	int target_number;
	double shut_time;
	double duration_in_sky;
	bool on_target;
};
//-------------------------------------------------------------------------------------------------------------------------
void Approach(Tower_Attack &mobile, pair<int,int> destination_cord, float dt){
	pair<float,float> v;
	float distance = sqrt( pow( (destination_cord.first - mobile.cord.first) , 2 ) + pow( (destination_cord.second - mobile.cord.second) , 2 ) );
	v.first = mobile.speed*( (destination_cord.first - mobile.cord.first))/distance;
	v.second = mobile.speed*( (destination_cord.second - mobile.cord.second))/distance;

	mobile.cord.first += int(v.first*dt);
	mobile.cord.second += int(v.second*dt);

	if( abs(mobile.cord.first - destination_cord.first) < 5 && abs(mobile.cord.second - destination_cord.second) < 5 )
		mobile.on_target = true;
}
//------------------------------------------------------------------------------------------------------------------

//main ++++++++++++++++++++++++++++
int main(){

	int lvl_choose;
	cout << "Enter number of level you want to play:" << endl;
	cout << "1) Spring\t 2)Winter" << endl;
	cin >> lvl_choose;

//Loading map ---------------------------------------------------------------------------------
	ifstream map_file;
	switch(lvl_choose){
		case 1:
			map_file.open (map1_details);
			break;
		case 2:
			map_file.open (map2_details);
			break;
	}

	int map_size;
		map_file >> map_size;

	int player_gold, player_people;
		map_file >> player_gold >> player_people;


	int lvl_waves_num;
		map_file >> lvl_waves_num;


	int *lvl_wave_turns_num;
		lvl_wave_turns_num = new int[lvl_waves_num];	
	
		for(int i=0; i<lvl_waves_num; i++)
			map_file >> lvl_wave_turns_num[i];


	int **lvl_wave_turns_units_num;
		lvl_wave_turns_units_num = new int*[lvl_waves_num];
		for(int i=0; i<lvl_waves_num; i++)
			lvl_wave_turns_units_num[i] = new int[lvl_wave_turns_num[i]];

		for(int i=0; i<lvl_waves_num; i++)
			for(int j=0; j<lvl_wave_turns_num[i]; j++)
				map_file >> lvl_wave_turns_units_num[i][j];


	double **start_wave_turns_time;
		start_wave_turns_time = new double*[lvl_waves_num];
		for(int i=0; i<lvl_waves_num; i++)
			start_wave_turns_time[i] = new double[lvl_wave_turns_num[i]];

		for(int i=0; i<lvl_waves_num; i++)
			for(int j=0; j<lvl_wave_turns_num[i]; j++)
				map_file >> start_wave_turns_time[i][j];


	int unit_total_num = 0;
		for(int i=0; i<lvl_waves_num; i++)
			for(int j=0; j<lvl_wave_turns_num[i]; j++)
				unit_total_num += lvl_wave_turns_units_num[i][j];


	Unit_live *unit_live = new Unit_live[unit_total_num];

		for(int i=0; i<unit_total_num; i++){
					int unit_form_int_form;
					map_file >> unit_form_int_form;
					unit_live[i].form = Unit_Form(unit_form_int_form);
				}


	int tower_places_num;
		map_file >> tower_places_num;
	int towers_size;
		map_file >> towers_size;

	Tower_Build *tower_build = new Tower_Build[tower_places_num];
		for(int i=0; i<tower_places_num; i++){
			map_file >> tower_build[i].little_cord.first >> tower_build[i].little_cord.second;
			map_file >> tower_build[i].large_cord.first >> tower_build[i].large_cord.second;
		}

	int turning_points_num;
		map_file >> turning_points_num;

	int width_of_turning_points;
		map_file >> width_of_turning_points;

	pair<int,int> mid_point_of_start;
	pair<int,int> mid_point_of_end;
	Turning_Point *turning_point = new Turning_Point[turning_points_num];
		map_file >> mid_point_of_start.first >> mid_point_of_start.second;
		for(int i=0; i<turning_points_num; i++){
			int turn_form_int_form;
			map_file >> turning_point[i].cord.first >> turning_point[i].cord.second >> turn_form_int_form;
			turning_point[i].direct = Direction(turn_form_int_form);
		}
		map_file >> mid_point_of_end.first >> mid_point_of_end.second;

	Direction start_direction;
		int start_direction_int_form;
		map_file >> start_direction_int_form;
		start_direction = Direction(start_direction_int_form);

	int num_of_tower_kinds = 4;
	int *tower_prices = new int[num_of_tower_kinds];
		for(int i=0; i<num_of_tower_kinds; i++)
			map_file >> tower_prices[i];
//------------------------------------------------------------------------------------------

//Loading units informations----------------------------------------------------------------
		for(int i=0; i<unit_total_num; i++){
			switch(unit_live[i].form){
				case orc:
					unit_live[i].size = width_of_turning_points*2/5;
					unit_live[i].health = 200;
					unit_live[i].speed = 42;
					unit_live[i].gold_recive = 5;
					unit_live[i].fight_power = 1;
					break;
				case armored:
					unit_live[i].size = width_of_turning_points*1/3;
					unit_live[i].health = 450;
					unit_live[i].speed = 21;
					unit_live[i].gold_recive = 8;
					unit_live[i].fight_power = 3;
					break;
				case wolf:
					unit_live[i].size = width_of_turning_points*3/8;
					unit_live[i].health = 100;
					unit_live[i].speed = 85;
					unit_live[i].gold_recive = 4;
					unit_live[i].fight_power = 1;
					break;
				case demon:
					unit_live[i].size = width_of_turning_points*1/3;
					unit_live[i].health = 400;
					unit_live[i].speed = 28;
					unit_live[i].gold_recive = 8;
					unit_live[i].fight_power = 3;
					break;
			}
			unit_live[i].prime_distance = rand()%(width_of_turning_points-unit_live[i].size) - width_of_turning_points/2;
			switch(start_direction){
				case Up:
					unit_live[i].cord.first = unit_live[i].prime_distance + (mid_point_of_start.first);
					unit_live[i].cord.second = mid_point_of_start.second - unit_live[i].size;
					break;
				case Down:
					unit_live[i].cord.first = unit_live[i].prime_distance + (mid_point_of_start.first);
					unit_live[i].cord.second = mid_point_of_start.second;
					break;
				case Right:
					unit_live[i].cord.first = mid_point_of_start.first - unit_live[i].size;
					unit_live[i].cord.second = unit_live[i].prime_distance + (mid_point_of_start.second);
					break;
				case Left:
					unit_live[i].cord.first = mid_point_of_start.first;
					unit_live[i].cord.second = unit_live[i].prime_distance + (mid_point_of_start.second);
					break;
			}
					unit_live[i].face = start_direction;
					unit_live[i].dead = false;
					unit_live[i].life_time = 0;
					unit_live[i].freazing = false;
					unit_live[i].start_freazing_time = 0;
		}
//----------------------------------------------------------------------------------------------

//define pngs-----------------------------------------------------------------------------------
	ifstream png_address_file;
	png_address_file.open(png_address);

	int num_of_lvls = 2;
	string map_png[num_of_lvls];

		for(int i=0; i<num_of_lvls; i++)
			getline(png_address_file , map_png[i]);

	int num_of_unit_kinds = 4;
	int num_of_unit_direction = 4;
	string unit_png[num_of_unit_kinds][num_of_unit_direction];

		for(int i=0; i<num_of_unit_kinds; i++)
			for(int j=0; j<num_of_unit_direction; j++)
				getline(png_address_file , unit_png[i][j]);

	string tower_png[num_of_tower_kinds];

		for(int i=0; i<num_of_tower_kinds; i++)
			getline(png_address_file , tower_png[i]);


	string cascel_png , upgrade_png , sell_png;

		getline(png_address_file , cascel_png);
		getline(png_address_file , upgrade_png);
		getline(png_address_file , sell_png);
//-----------------------------------------------------------------------------------------------

//Start graphic----------------------------------------------------------------------------------

	Window w(map_size,map_size);
		w.clear();

		srand(time(0));

	bool victory = false;
	bool check_for_next_wave = true;
	int tower_range = 85;
	int units_in_map = 0;
	int waves_in_map = 0;
	int last_wave_part_in_map =0;
	int number_of_tower_building;
	bool tower_building = false;
	bool need_more_gold = false;

	vector<Tower_Attack> tower_attack;

	auto Start_time = system_clock::now();
	auto former_now_time = Start_time;

	Event E;

	while(!victory && player_people>0){
		w.clear();

		E = w.pollForEvent();
		auto Right_now_time = system_clock::now();

		duration<double> delay_of_start_time_mood = Right_now_time - Start_time;
		double delay_of_start = delay_of_start_time_mood.count();

		duration<double> time_past_time_mood = Right_now_time - former_now_time;
		double time_past = time_past_time_mood.count();

		//Quit**************************************
		if(E.type()==QUIT)
			return 0;

		//mouse act***********************************
		if(E.type()==LCLICK){
			pair<int,int> click_cord;
			click_cord.first = E.mouseX();
			click_cord.second = E.mouseY();

			//try to build tower***********************
			for(int i=0; i<tower_places_num; i++)
				//if( !tower_build[i].exist )
				if( click_cord.first >= tower_build[i].little_cord.first && click_cord.first <= tower_build[i].large_cord.first
				&&  click_cord.second >= tower_build[i].little_cord.second && click_cord.second <= tower_build[i].large_cord.second ){
					tower_building = true;
					number_of_tower_building = i;
				}
			//choose to build*******************
			if(tower_building)
				if(click_cord.second >= map_size-2*towers_size){

					if(click_cord.first <= 2*towers_size){
						if(tower_build[number_of_tower_building].exist)
							continue;
						if(player_gold < tower_prices[archer]){
							need_more_gold = true;
							continue;
						}
						else need_more_gold = false;

						tower_build[number_of_tower_building].kind = archer;
						tower_build[number_of_tower_building].damage = 50;
						tower_build[number_of_tower_building].attack_speed = 0.7;
						tower_build[number_of_tower_building].size = towers_size;
						player_gold -= tower_prices[archer];
						tower_build[number_of_tower_building].last_time_shut = delay_of_start;
						tower_build[number_of_tower_building].exist = true;
					}
					else if(click_cord.first <= 4*towers_size){
						if(tower_build[number_of_tower_building].exist)
							continue;
						if(player_gold < tower_prices[canon]){
							need_more_gold = true;
							continue;
						}
						else need_more_gold = false;

						tower_build[number_of_tower_building].kind = canon;
						tower_build[number_of_tower_building].damage = 140;
						tower_build[number_of_tower_building].attack_speed = 2;
						tower_build[number_of_tower_building].size = towers_size;
						player_gold -= tower_prices[canon];
						tower_build[number_of_tower_building].last_time_shut = delay_of_start;
						tower_build[number_of_tower_building].exist = true;
					}
					else if(click_cord.first <= 6*towers_size){
						if(tower_build[number_of_tower_building].exist)
							continue;
						if(player_gold < tower_prices[mage]){
							need_more_gold = true;
							continue;
						}
						else need_more_gold = false;

						tower_build[number_of_tower_building].kind = mage;
						tower_build[number_of_tower_building].damage = 140;
						tower_build[number_of_tower_building].attack_speed = 1.5;
						tower_build[number_of_tower_building].size = towers_size;
						player_gold -= tower_prices[mage];
						tower_build[number_of_tower_building].last_time_shut = delay_of_start;
						tower_build[number_of_tower_building].exist = true;
					}
					else if(click_cord.first <= 8*towers_size){
						if(tower_build[number_of_tower_building].exist)
							continue;
						if(player_gold < tower_prices[icy]){
							need_more_gold = true;
							continue;
						}
						else need_more_gold = false;

						tower_build[number_of_tower_building].kind = icy;
						tower_build[number_of_tower_building].damage = 30;
						tower_build[number_of_tower_building].attack_speed = 2;
						tower_build[number_of_tower_building].size = towers_size;
						player_gold -= tower_prices[icy];
						tower_build[number_of_tower_building].last_time_shut = delay_of_start;
						tower_build[number_of_tower_building].exist = true;
					}
					else if(click_cord.first <= 10*towers_size){
						if(!tower_build[number_of_tower_building].exist)
							continue;
						if(player_gold < tower_prices[tower_build[number_of_tower_building].kind]){
							need_more_gold = true;
							continue;
						}
						need_more_gold = false;
						tower_build[number_of_tower_building].attack_speed /= 2;
						tower_build[number_of_tower_building].size += towers_size/10;
						player_gold -= tower_prices[tower_build[number_of_tower_building].kind];
					}
					else if(click_cord.first <= 12*towers_size){
						if(!tower_build[number_of_tower_building].exist)
							continue;
						player_gold += tower_prices[tower_build[number_of_tower_building].kind]/2;
						tower_build[number_of_tower_building].exist = false;
					}
					else if(click_cord.first <= 13*towers_size)
						tower_building = false;
				}
		}

		//former unit movements***********************
		for(int i=0; i<units_in_map; i++){

			if(unit_live[i].dead) continue;

			double Adder_life_time = delay_of_start - unit_live[i].start_living_time - unit_live[i].life_time;
			//unfreazing****************************
			if(unit_live[i].freazing && delay_of_start - unit_live[i].start_freazing_time >= 3){
				unit_live[i].start_freazing_time = 0;
				unit_live[i].freazing = false;
				unit_live[i].speed *= 2;
			}
			//move*************************************
			if(Adder_life_time*unit_live[i].speed >= 1){

				switch(unit_live[i].face){
					case Up:
						unit_live[i].cord.second -= Adder_life_time*unit_live[i].speed;
						break;
					case Down:
						unit_live[i].cord.second += Adder_life_time*unit_live[i].speed;
						break;
					case Right:
						unit_live[i].cord.first += Adder_life_time*unit_live[i].speed;
						break;
					case Left:
						unit_live[i].cord.first -= Adder_life_time*unit_live[i].speed;
						break;
				}
				//turn***********
				for(int j=0; j<turning_points_num; j++){
					
					bool should_to_turn = false;
					if(pow(unit_live[i].cord.first-turning_point[j].cord.first , 2) + pow(unit_live[i].cord.second-turning_point[j].cord.second , 2) <= pow(width_of_turning_points-unit_live[i].prime_distance,2) )
					switch(unit_live[i].face){
						case Up:
							if(unit_live[i].cord.second < turning_point[j].cord.second)
								if( abs(unit_live[i].cord.second-turning_point[j].cord.second) >= abs(unit_live[i].prime_distance)/2 )
									should_to_turn = true;
							break;
						case Right:
							if(unit_live[i].cord.first > turning_point[j].cord.first)
					 			if( abs(unit_live[i].cord.first-turning_point[j].cord.first) >= abs(unit_live[i].prime_distance)/2 )
									should_to_turn = true;
								break;
						case Down:
							if(unit_live[i].cord.second > turning_point[j].cord.second)
								if( abs(unit_live[i].cord.second-turning_point[j].cord.second) >= abs(unit_live[i].prime_distance)/2 )
									should_to_turn = true;
							break;
						case Left:
							if(unit_live[i].cord.first < turning_point[j].cord.first)
								if( abs(unit_live[i].cord.first-turning_point[j].cord.first) >= abs(unit_live[i].prime_distance)/2 )
									should_to_turn = true;
								break;
					}

					if(should_to_turn)
						unit_live[i].face =turning_point[j].direct;
				}
									
							
				unit_live[i].life_time += Adder_life_time;
			}
			//arrive to finish line*********
			if(unit_live[i].cord.first < 0 || unit_live[i].cord.second < 0
			|| unit_live[i].cord.first > map_size || unit_live[i].cord.second > map_size){
				player_people -= unit_live[i].fight_power;
				unit_live[i].dead = true;
			}
		}
		//towers shuts********************************
		for(int i=0; i<tower_places_num; i++){
			
			if(!tower_build[i].exist)
				continue;

			for(int j=0; j<units_in_map; j++){
	
				if(unit_live[j].dead)
					continue;

				if(delay_of_start - tower_build[i].last_time_shut < tower_build[i].attack_speed)
					continue;
	
				if( ( pow( (tower_build[i].little_cord.first + towers_size/2 - unit_live[j].cord.first) , 2 ) + pow( (tower_build[i].little_cord.second + towers_size/2 - unit_live[j].cord.second) , 2 ) ) <= pow(tower_range , 2) ){
					tower_build[i].last_time_shut = delay_of_start;
					Tower_Attack new_tower_attack;
					new_tower_attack.type = tower_build[i].kind;
					new_tower_attack.target_number = j;
					new_tower_attack.cord = tower_build[i].little_cord;
					switch(new_tower_attack.type){
						case archer:
						case canon:
							switch(unit_live[j].form){
								case armored:
									new_tower_attack.damage = tower_build[i].damage/2;
									break;
								default:
									new_tower_attack.damage = tower_build[i].damage;
							}
						case mage:
						case icy:
							switch(unit_live[j].form){
								case demon:
									new_tower_attack.damage = tower_build[i].damage/2;
									break;
								default:
									new_tower_attack.damage = tower_build[i].damage;
							}
							break;
					}
					int damage;
					new_tower_attack.speed = 400;
					new_tower_attack.shut_time = delay_of_start;
					new_tower_attack.duration_in_sky = 0;
					new_tower_attack.on_target = false;

					tower_attack.push_back(new_tower_attack);
				}
			}
		}
		//shuts move******************************
		for(int i=0; i<tower_attack.size(); i++){

			if(unit_live[tower_attack[i].target_number].dead){
				tower_attack.erase( tower_attack.begin()+i );
				i--;
				continue;
			}

			double Adder_shut_time = delay_of_start - tower_attack[i].shut_time - tower_attack[i].duration_in_sky;
			if(Adder_shut_time*tower_attack[i].speed >= 1){

				Approach(tower_attack[i], unit_live[tower_attack[i].target_number].cord, Adder_shut_time);
				tower_attack[i].duration_in_sky += Adder_shut_time;
			}

		}
			
		for(int i=0; i<tower_attack.size(); i++)
			if(tower_attack[i].on_target){
				switch(tower_attack[i].type){
					case canon:
						for(int j=0; j<tower_attack[i].target_number; j++)
							if(!unit_live[j].dead)
								if( pow(unit_live[tower_attack[i].target_number].cord.first - unit_live[j].cord.first , 2) + pow(unit_live[tower_attack[i].target_number].cord.second - unit_live[i].cord.second , 2) <= pow(50 , 2) ){
									if(unit_live[tower_attack[i].target_number].form == armored && unit_live[j].form != armored)
										unit_live[j].health -= 2*tower_attack[i].damage;
									else unit_live[j].health -= tower_attack[i].damage;
									if(unit_live[j].health <= 0){
										unit_live[j].dead = true;
										player_gold += unit_live[j].gold_recive;
									}
								}
						for(int j=tower_attack[i].target_number+1; j<units_in_map; j++)
							if(!unit_live[j].dead)
								if( pow(unit_live[tower_attack[i].target_number].cord.first - unit_live[j].cord.first , 2) + pow(unit_live[tower_attack[i].target_number].cord.second - unit_live[i].cord.second , 2) <= pow(50 , 2) ){
									if(unit_live[tower_attack[i].target_number].form == armored && unit_live[j].form != armored)
										unit_live[j].health -= 2*tower_attack[i].damage;
									else unit_live[j].health -= tower_attack[i].damage;
									if(unit_live[j].health <= 0){
										unit_live[j].dead = true;
										player_gold += unit_live[j].gold_recive;
									}
								}
						break;
					case icy:
						for(int j=0; j<tower_attack[i].target_number; j++)
							if(!unit_live[j].dead && !unit_live[j].freazing)
								if( pow(unit_live[tower_attack[i].target_number].cord.first - unit_live[j].cord.first , 2) + pow(unit_live[tower_attack[i].target_number].cord.second - unit_live[i].cord.second , 2) <= pow(50 , 2) ){
									if(unit_live[tower_attack[i].target_number].form == demon && unit_live[j].form != demon)
										unit_live[j].health -= 2*tower_attack[i].damage;
									else unit_live[j].health -= tower_attack[i].damage;
									if(unit_live[j].health <= 0){
										unit_live[j].dead = true;
										player_gold += unit_live[j].gold_recive;
									}
									unit_live[j].freazing = true;
									unit_live[j].start_freazing_time = delay_of_start;
									unit_live[j].speed /= 2;
								}
						for(int j=tower_attack[i].target_number+1; j<units_in_map; j++)
							if(!unit_live[j].dead && !unit_live[j].freazing)
								if( pow(unit_live[tower_attack[i].target_number].cord.first - unit_live[j].cord.first , 2) + pow(unit_live[tower_attack[i].target_number].cord.second - unit_live[i].cord.second , 2) <= pow(50 , 2) ){
									if(unit_live[tower_attack[i].target_number].form == demon && unit_live[j].form != demon)
										unit_live[j].health -= 2*tower_attack[i].damage;
									else unit_live[j].health -= tower_attack[i].damage;
									if(unit_live[j].health <= 0){
										unit_live[j].dead = true;
										player_gold += unit_live[j].gold_recive;
									}
									unit_live[j].freazing = true;
									unit_live[j].start_freazing_time = delay_of_start;
									unit_live[j].speed /= 2;
								}
						if(!unit_live[tower_attack[i].target_number].freazing){
							unit_live[tower_attack[i].target_number].freazing = true;
							unit_live[tower_attack[i].target_number].start_freazing_time = delay_of_start;
							unit_live[tower_attack[i].target_number].speed /= 2;
						}
						break;
				}
				unit_live[tower_attack[i].target_number].health -= tower_attack[i].damage;
				if(unit_live[tower_attack[i].target_number].health <= 0){
					unit_live[tower_attack[i].target_number].dead = true;
					player_gold += unit_live[tower_attack[i].target_number].gold_recive;
				}
				tower_attack.erase( tower_attack.begin()+i );
			}
			
		//new wave or group*************************
		if(check_for_next_wave)
		if(delay_of_start >= start_wave_turns_time[waves_in_map][last_wave_part_in_map]){

			last_wave_part_in_map++;
			if(last_wave_part_in_map > lvl_wave_turns_num[waves_in_map]){
				
				last_wave_part_in_map = 0;
				waves_in_map++;
				if(waves_in_map == lvl_waves_num){
					waves_in_map = 0;
					check_for_next_wave = false;
				}
			}

			if(check_for_next_wave)
			for(int i=0; i<lvl_wave_turns_units_num[waves_in_map][last_wave_part_in_map-1]; i++){
				unit_live[units_in_map].start_living_time = delay_of_start;
				units_in_map++;
			}
		}
		//drow all*****************************************
		w.draw_bg(map_png[lvl_choose-1],0,0);

			//drow units
			for(int i=0; i<units_in_map; i++)
				if(!unit_live[i].dead){
				w.draw_png( unit_png[unit_live[i].form][unit_live[i].face] ,
							unit_live[i].cord.first , unit_live[i].cord.second-unit_live[i].size ,
							unit_live[i].size , unit_live[i].size );
				w.draw_line(unit_live[i].cord.first, unit_live[i].cord.second,
							unit_live[i].cord.first + unit_live[i].health/5, unit_live[i].cord.second, GREEN);
				}

			//drow towers
			for(int i=0; i<tower_places_num; i++)
				if(tower_build[i].exist)
					w.draw_png( tower_png[tower_build[i].kind] ,
								tower_build[i].little_cord.first , tower_build[i].little_cord.second-towers_size/2 ,
								tower_build[i].size , tower_build[i].size );
			//drow shuts
			for(int i=0; i<tower_attack.size(); i++)
				switch(tower_attack[i].type){
					case archer:
						w.fill_rect(tower_attack[i].cord.first+unit_live[tower_attack[i].target_number].size/2, tower_attack[i].cord.second-unit_live[tower_attack[i].target_number].size/2, 5,3, BLACK);
						break;
					case canon:
						w.fill_rect(tower_attack[i].cord.first+unit_live[tower_attack[i].target_number].size/2, tower_attack[i].cord.second-unit_live[tower_attack[i].target_number].size/2, 10,10, BLACK);
						break;
					case mage:
						w.fill_rect(tower_attack[i].cord.first+unit_live[tower_attack[i].target_number].size/2, tower_attack[i].cord.second-unit_live[tower_attack[i].target_number].size/2, 5,5, CYAN);
						break;
					case icy:
						w.fill_rect(tower_attack[i].cord.first+unit_live[tower_attack[i].target_number].size/2, tower_attack[i].cord.second-unit_live[tower_attack[i].target_number].size/2, 5,5, BLUE);
						break;
				}

			//write txts
			w.show_text("Alive people: " + to_string(player_people), map_size/200, map_size/200, RED, standard_font, map_size/20);
			w.show_text("Gold: " + to_string(player_gold), map_size/200, map_size/200+map_size/20, YELLOW, standard_font, map_size/20);
			if(need_more_gold)
				w.show_text("Need More Gold---", map_size/200, map_size/200+2*map_size/20, RED, standard_font, map_size/20);

			//drow towers for choos
			if(tower_building){
				w.draw_rect(tower_build[number_of_tower_building].little_cord.first+towers_size/2-tower_range , tower_build[number_of_tower_building].little_cord.second+towers_size/2-tower_range,
							2*tower_range, 2*tower_range , MAGENTA);

				w.draw_rect( 0			  , map_size-2*towers_size, 2*towers_size, 2*towers_size, WHITE);
				w.draw_rect( 2*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size, WHITE);
				w.draw_rect( 4*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size, WHITE);
				w.draw_rect( 6*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size, WHITE);
				w.draw_rect( 8*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size, WHITE);
				w.draw_rect(10*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size, WHITE);
				w.draw_rect(12*towers_size, map_size-2*towers_size,   towers_size, 2*towers_size, WHITE);

				w.draw_png(tower_png[archer], 0			   , map_size-2*towers_size, 2*towers_size, 2*towers_size);
				w.draw_png(tower_png[canon] , 2*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size);
				w.draw_png(tower_png[mage]  , 4*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size);
				w.draw_png(tower_png[icy]   , 6*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size);
				w.draw_png(upgrade_png   	, 8*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size);
				w.draw_png(sell_png		   	,10*towers_size, map_size-2*towers_size, 2*towers_size, 2*towers_size);
				w.draw_png(cascel_png   	,12*towers_size, map_size-2*towers_size,   towers_size, 2*towers_size);
				
				w.show_text(to_string(tower_prices[0])+"       "+to_string(tower_prices[1])+"     "+to_string(tower_prices[2])+"       "+to_string(tower_prices[3]),
							map_size/200, map_size+map_size/200-2*towers_size, BLACK, standard_font, map_size/20);
				w.show_text("Tower Price   Half Price", map_size/200+8*towers_size, map_size+map_size/200-2*towers_size, BLACK, standard_font, map_size/40);

				}
		//last
		auto former_now_time = Start_time;
		w.update_screen();

		victory = true;
		for(int i=0; i<unit_total_num; i++)
			if(!unit_live[i].dead)
				victory = false;
	}
	

	w.clear();
	if(victory)
		w.show_text("VICTORY", map_size/6, map_size/3, GREEN, standard_font, map_size/6);
	else
		w.show_text("GAME OVER", map_size/6, map_size/3, RED, standard_font, map_size/8);
	w.update_screen();


	auto last_time = system_clock::now();
	double time_past = 0;
	while(time_past < 5){
		auto Right_now_time = system_clock::now();
		duration<double> time_past_time_mood = Right_now_time - last_time;
		time_past = time_past_time_mood.count();
	}


	return 0;

}