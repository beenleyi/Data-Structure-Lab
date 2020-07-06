#include"struct.h"
extern city cities[CITY_NUM];
extern void get_my_time(my_time &);
extern void add_time(my_time &, int);
extern void add_time(my_time &, int);

void log_input(const request & user_request){
	ofstream log;
    log.open("travel_simulation.log",ios_base::app);
	my_time cur_time;
    get_my_time(cur_time);
    log <<endl<<endl;
    log <<"-----------------------";
    log << cur_time.year<<"-"<<cur_time.month<<"-"<<cur_time.day<<" "<<setw(2)<<setfill('0')<<cur_time.hour<<":"<<setw(2)<<setfill('0')<<cur_time.minute;
    log <<"-----------------------"<<endl;
    log <<"User ID: "<< user_request.id<<endl;
	log<<"User request: from "<<cities[user_request.dept_city_no].city_name<<" to "<<cities[user_request.dst_city_no].city_name;
	if (user_request.travel_type == 1) log<<" with the least risk in "<<user_request.limited_time <<" hours."<<endl;
	else log<<" with the least risk."<<endl;
	return;
	log.close();
}

void log_output(const route_info & best_route, int dst_city_no){
	ofstream log;
    log.open("travel_simulation.log",ios_base::app);
	route_ptr i;
    i = best_route.detail_route->next_ptr;
    if(i==NULL){
        log<<"****ERROR****\n Can NOT find one route which meet your require!"<<endl;
        return;
    }
	log<<"The best route is\n";
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
        log << temp_time.year<<"-"<<temp_time.month<<"-"<<temp_time.day<<" "<<setw(2)<<setfill('0')<<temp_time.hour<<":"<<setw(2)<<setfill('0')<<temp_time.minute;
		log<<", arrival_time at ";
		add_time(temp_time, i->vehicle_time);
        log << temp_time.year<<"-"<<temp_time.month<<"-"<<temp_time.day<<" "<<setw(2)<<setfill('0')<<temp_time.hour<<":"<<setw(2)<<setfill('0')<<temp_time.minute << endl;
		i=i->next_ptr;
	}
    log<<"The total time is "<<best_route.total_time<<"h."<<endl;
    log<<"The total risk is "<<best_route.total_risk<<"."<<endl<<endl;
	log.close();
}

void log_simulation(const route_info & best_route,int dst_city_no){
        freopen("travel_simulation.log","a",stdout);
        route_ptr i;
        i = best_route.detail_route->next_ptr;
        my_time cur_time;
        int temp_hour;
        while(i){
            cur_time = i->arrival_time;
            temp_hour = i->wait_time;
            while(temp_hour--){
                printf("It's %02d-%02d-%02d %02d:%02d now. ", cur_time.year, cur_time.month, cur_time.day, cur_time.hour,cur_time.minute);
                printf("You are waiting at ");
                cout << cities[i->city_no].city_name<<"."<<endl;
                add_time(cur_time, 1);
            }
            temp_hour = i->vehicle_time;
            while(temp_hour--){
                printf("It's %d-%02d-%02d %02d:%02d now.", cur_time.year, cur_time.month, cur_time.day, cur_time.hour,cur_time.minute);
                printf(" You are on a ");
                if (i->vehicle == 0) printf("plane. This plane is flying to ");
                else if(i->vehicle == 1) printf("train. This train is bound to ");
                else printf("car. Next stop is ");
                if (i->next_ptr) cout << cities[i->next_ptr->city_no].city_name<<"." << endl;
                else cout<<"the destination--"<<cities[dst_city_no].city_name<<"."<<endl;
                add_time(cur_time, 1);
            }
            i = i->next_ptr;
        }
        printf("It's % d-%02d-%02d % 02d:%02d now.", cur_time.year, cur_time.month, cur_time.day, cur_time.hour, cur_time.minute);
        printf("You have arrived in the destination!\n");
        fclose(stdout);
}
