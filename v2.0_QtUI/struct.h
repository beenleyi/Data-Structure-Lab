#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<fstream>
#include<time.h>
#include<windows.h>
using namespace std;
const int CITY_NUM = 20;
const int INF= 100000000;
const double city_risk_no2value[3]={0.9, 0.5, 0.2};
const int vehicle_risk_no2value[3]={9, 5, 2};
const int total_city = 11;
const int TIME_SCALE=50;

struct my_time{
  int year;
  int month;
  int day;
  int hour;
  int minute;
};

struct my_clock{
  int hour;
  int minute;
};

struct vehicle{
    int type;
    int dst_city_no;
    my_clock start_time;
    my_clock time_spent;
};

struct city{
    int city_risk_no;//城市风险编号
    string city_name;
    vector < vehicle >  my_vehicle;
    int posx;
    int posy;
};

struct request{
  string id;
  int dept_city_no;//source address 
  int dst_city_no;//destination address
  int travel_type;//0:least risk type; 1:least risk type in limited time
  int limited_time;//hour
};

struct route{
    int wait_time;//wait for the vehicle at city_no, hour
    my_time arrival_time;
    int city_no;
    int vehicle;//use what vehicle to next addr;
    int vehicle_time;//spend how much time to next addr;
//    int wait_risk;//wait for the vehicle with how much risk;
    route * next_ptr;
};
typedef route * route_ptr;

struct route_info
{
	double total_risk;
	int total_time;
	route_ptr detail_route;
};

