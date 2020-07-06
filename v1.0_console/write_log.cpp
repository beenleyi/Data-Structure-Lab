#include"struct.h"

extern city cities[CITY_NUM];
extern void get_time(my_time &);
extern void add_time(my_time &, int);

void log_input(const request & user_request){
	ofstream log;
	log.open("travel_simulation.log");	
	my_time cur_time;
	get_time(cur_time);
	log << cur_time.year<<"-"<<cur_time.month<<"-"<<cur_time.day<<" "<<setw(2)<<setfill('0')<<cur_time.hour<<":"<<cur_time.minute << endl;
	log<<"User request: from "<<cities[user_request.dept_city_no].city_name<<" to "<<cities[user_request.dst_city_no].city_name;
	if (user_request.travel_type == 1) log<<" with the least risk in "<<user_request.limited_time <<" hours."<<endl;
	else log<<" with the least risk."<<endl;
	return;
	log.close();
}

void log_output(const route_info & best_route, int dst_city_no){
	ofstream log;
	log.open("travel_simulation.log",ios::app);
	route_ptr i;
	log<<"The best route is\n";
	i = best_route.detail_route->next_ptr;
	if (i == NULL) {
		log<<"****ERROR****\n Can NOT find one route which meet your require!";
		return;
	}
	while(i){
		log << cities[i->city_no].city_name<<"--->";
		if (i->next_ptr) log << cities[i->next_ptr->city_no].city_name; else log <<  cities[dst_city_no].city_name;
		if (i->vehicle == 0) log << " by plane";
		else if (i->vehicle == 1) log<<" by train";
		else log << " by car";
		log << ", start at ";
		my_time temp_time;
		temp_time = i->arrival_time;
		add_time(temp_time, i->wait_time);
		log << temp_time.year<<"-"<<temp_time.month<<"-"<<temp_time.day<<" "<<setw(2)<<setfill('0')<<temp_time.hour<<":"<<temp_time.minute;
		log<<", arrival_time at ";
		add_time(temp_time, i->vehicle_time);
		log << temp_time.year<<"-"<<temp_time.month<<"-"<<temp_time.day<<" "<<setw(2)<<setfill('0')<<temp_time.hour<<":"<<temp_time.minute << endl;
		i=i->next_ptr;
	}
	log<<"The total time is "<<best_route.total_time;
	log<<"The total risk is "<<best_route.total_risk;
	log.close();
}