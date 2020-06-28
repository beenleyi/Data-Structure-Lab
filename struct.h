#include<iostream>
using namespace std;
#include <string>
#include<vector>
const int TOTAL_CITY_NUM = 10;
struct time
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

struct vehicle{
    int type;
    string dst_city;
    time start_time;
    time end_time;
};

struct city{
    int city_risk;//城市风险编号
    string city_name;
    vector < vehicle >  my_vehicle;
};

struct input{
  int src_city_no;//source address 
  int dst_city_no;//destination address
  int travel_type;//0:least risk type;1:least risk type in limited time
};

struct route{
    int wait_time;//wait for the vehicle at addr;
    int city_no;
    int vehicle;//use what vehicle to next addr;
    int vehicle_time;//spend how much time to next addr;
//    int wait_risk;//wait for the vehicle with how much risk;
    int next_ptr;
};
typedef route * route_ptr;

struct route_info
{
	int total_risk;
	int total_time;
	route_ptr detail_route;
};
typedef route_info* route_info_ptr;

struct output{
    time start_time;
    time end_time;
    int src_city_no;
    int dst_city_no;
    route_info_ptr best_route;
};